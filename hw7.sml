(*  COMP 212 Homework 7:  AVL trees
*   
*   Lance Gartrell
*)


structure Hw7 =
struct

  (*  The type of an AVL binary search tree.  
  *
  *  Invariants:
  *  - For any tree N(x, n, t1, t2), keys(t1) < x < keys(t2).
  *  - For any tree t = N(x, h, t1, t2), h is the height of t.
  *  - For any tree t = N(x, h, t1, h2), |height(t1) - height(t2)| <= 1.
  *)
  datatype tree = E | N of int * int * tree * tree

  (*  toString item_toString t = a string representation of the tree t.
  *
  *  DO NOT CHANGE THE DEFINITION OF THIS FUNCTION!
  *)
  fun toString (t : tree) : string =
  let
    (*  pad(s, n1, m1, m2, n2) =
    *     "    ----" ^ s ^ "----    "
    *   (n1 leading spaces, m1 leading dashes, m2 trailing dashes, n2 trailing
    *   spaces).
    *)
    fun pad(s, n1, m1, m2, n2) =
      (implode (List.tabulate(n1, fn _ => #" "))) ^
      (implode (List.tabulate(m1, fn _ => #"-"))) ^
      s ^
      (implode (List.tabulate(m2, fn _ => #"-"))) ^
      (implode (List.tabulate(n2, fn _ => #" ")))

    (*  merge ([s_0,...], n1, [s_0',...], n2, n) =
    *     [..., s_i ^ "   " ^ s_i',...]
    *     (n spaces).  Each element of the result list has length n1+n+n2.
    *)
    fun merge(ss1 : string list, n1 : int, ss2 : string list, n2 : int, n) :
        string list =
      case (ss1, ss2) of
           ([], _) => map (fn s => pad (s, n1+n, 0, 0, 0)) ss2
         | (_, []) => map (fn s => pad (s, 0, 0, 0, n2+n)) ss1
         | (s1 :: ss1, s2 :: ss2) =>
             ((pad(s1, 0, 0, 0, n div 2)) ^ (pad(s2, n-(n div 2), 0, 0, 0))) ::
               merge(ss1, n1, ss2, n2, n)

    (*  treeToString(t) = ([s_0,...,s_{m-1}], n, m1, m2), where:
    *     * s_0 ^ "\n" ^ s_1 ^ "\n" ^ ... ^ "\n" ^ s_{m-1} is a string
    *       representation of t.
    *     * String.size(s_i) = n for all i.
    *     * String.sub(s_0, m1) is the first character of the root rep'n
    *       in s_0.
    *     * String.sub(s_0, n1) is the last character of the root rep'n
    *       in s_0.
    *)
    fun treeToString (t : tree) : (string list)*int*int*int =
      case t of
           E => (["[]"], 2, 0, 1)
         | N(x, r, t1, t2) =>
             let
               val (ss1, n1, m11, m12) = treeToString t1
               val (ss2, n2, m21, m22) = treeToString t2
               val s = String.concat [Int.toString x, "(", Int.toString r, ")"]
               val n = String.size s
             in
               (pad(s, m11, n1-m11, m22+1, n2-m22-1) :: 
                 merge(ss1, n1, ss2, n2, n),
                 n1+n2+n, n1, n1+n-1)
             end

    val (lines, _, _, _) = treeToString t
  in
    String.concatWith "\n" lines ^ "\n"
  end

  (* height(t) = h where, 
   *              
   *     h is the height of t, the longest root of t
   *)
  fun height(t : tree) : int =
    case t of E => 0
    | N(_, h, _, _) => h

  (* node(i, t0, t1) = n where, 
   *                   
   *    n is a tree representation with root value i 
   *    and a computed height component: 1 + the maximum height of t0 and t1,
   *    the children of t. 
   *)
  fun nodeWithHeight(i : int, t0 : tree, t1 : tree) : tree =  
    let 
      val h0 : int = height(t0)
      val h1 : int = height(t1)
      val nodeHeight : int = 1 + Int.max(h0, h1)
    in
      N(i, nodeHeight, t0, t1)
    end

  (* rotate_left(t as N(x, h, t0, t1)) = N(x', h', t0', t1') 
   *
   *    returns an avl tree in which:
   *    - x' represents the the root value of t1
   *    - h' represents the height of the rotated tree
   *    - t0' represents the left sibling tree with root value x 
   *          where the left sibling trees is t0 and the right sibling tree 
   *          is the left sibling tree of t1
   *    - t1' represents the right sibling tree of t1
   *
   * Pre conditions: t is non-empty
   *)
  fun rotate_left(t as N(z, h, t0, t1) : tree) : tree =
    case t1 of E => t
    |  N(y, _, t0', t1') => nodeWithHeight(y, nodeWithHeight(z, t0, t0'), t1')

  (* rotate_right(t as N(y, h, t0, t1)) =  N(y', h', t0', t1') 
   *
   *     returns an avl tree in which:
   *     - y' represents the root value of t0
   *     - h' represents the height of the rotated tree (h)
   *     - t0' represents the left sibling tree of t0
   *     - t1' represents the left sibling tree with root value y 
   *           where the left sibling tree is the right sibling tree of t0 
   *           and the right sibling tree is t1
   *           
   * Pre conditions: t is non-empty       
   *)
  fun rotate_right(t as N(y, h, t0, t1) : tree) : tree =
    case t0 of E => t
    |  N(x, _, t0', t1') => nodeWithHeight(x, t0', nodeWithHeight(y, t1', t1))

  (* heightDiff(t) = x where:
   *    
   *    x is the difference in height 
   *    between the the sibling trees of t
   *
   * Pre conditions: t is non-empty
   *)
  fun heightDiff(t as N(i, h, t0, t1) : tree ) : int = 
    let 
      val h0L : int = height(t0)
      val h1R : int = height(t1)
    in
      h0L - h1R
    end

  (* rotateCheck(t) = t', where: 
   *
   *      t' is an AVL tree in which the sibling  
   *      heights differ by a maximum height of 1       
   *
   * Pre conditions: t is non-empty              
   *)
  fun rotateCheck(t as N(x, h, t0, t1) : tree ) : tree = 
    let 
      val tHeight : int = heightDiff(t)
    in 
      if tHeight > 1 then  
        if heightDiff(t0) = ~1 then  
          let 
            val lRotTree : tree = nodeWithHeight(x, rotate_left(t0), t1) 
          in 
            rotate_right(lRotTree) 
          end  
        else rotate_right(t) 
      else if tHeight < ~1 then 
        if heightDiff(t1) = 1 then
          let 
            val rRotTree : tree = nodeWithHeight(x, t0, rotate_right(t1))
          in 
            rotate_left(rRotTree) 
          end 
        else rotate_left(t)
      else t 
    end

  (*  member(t, x) = true,  if x is an element of keys(t)
  *                  false, otherwise.
  *)
  fun member (t : tree, x : int) : bool =
     case t of
         E => false
       | N(y, _, t0, t1) =>
           if x = y then true
           else if x < y then member(t0, x)
           else member(t1, x)

  (*  add(t, x) = t', where keys(t') = keys(t) + {x}.  + represents
  *   set-theoretic union.
  *)
  fun add(t : tree, x : int) : tree =
    case t of 
        E => N(x, 1, E, E)
      | N(y, _, t0, t1) => 
          if x = y then t
          else if x < y then
            let
              val t0' : tree = add(t0, x)
            in
              rotateCheck(nodeWithHeight(y, t0', t1))
            end 
          else 
            let
              val t1' : tree = add(t1, x)
            in
              rotateCheck(nodeWithHeight(y, t0, t1'))
            end 

  (*  delete(t, x) = t', where keys(t') = keys(t) - {x}.  - represents
  *  set-theoretic difference.
  *)
  fun delete(t : tree, x : int) : tree = 
    case t of E => N(x, 1, E, E)
      | N(y, _, t0, t1) => 
          if x = y then  
            case t of 
                N(_, _, E, s1) => t1
              | N(_, _, s0, E) => t0
              | _ => 
                let 

                (*  deleteMax(t) = (c',v), where keys(c') = keys(t) - {v} - represents
                 *  set-theoretic difference.
                 *
                 *          - c' represents the modified AVL tree after removing  
                 *          the maximum value from t
                 *          - v represents the maximum value from t (the removed value)

                 * Pre conditions: t is non-empty
                 *)
                  fun deleteMax(t : tree) : tree*int = 
                    case t of 
                      N(s, _, E, c1) => (c1,s)
                    | N(s, _, c0, c1) => 
                      let 
                        val (c0', s') : tree*int = deleteMax(c0) 
                      in 
                        (rotateCheck(nodeWithHeight(s, c0', c1)), s') 
                      end

                  val (t', w) : tree*int = deleteMax(t1) 
                in 
                  rotateCheck(nodeWithHeight(w, t0, t')) 
                end  
           else if x < y then rotateCheck(nodeWithHeight(y, delete(t0, x), t1))
           else rotateCheck(nodeWithHeight(y, t0, delete(t1, x)))  
end

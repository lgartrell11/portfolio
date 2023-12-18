(*  COMP 212 Homework 9:  higher-order functions.
*
*  A string*'a dictionary implementation in which the dictionary is backed
*  by a (string*'a) list.
*
*  N. Danner
*)

structure Hw9 =
struct

  (* The type of dictionaries with string keys and type 'a values.
  *
  * Invariant:  if [(k_0,v_0),...,(k_{n-1}, d_{n-1})] : 'a dict, then
  * k_i ≠ k_j for 0 ≤ i, j < n-1.
  *)
  type 'a dict = (string*'a) list

  exception NotFound

  (*  empty = the empty dictionary.
  *)
  val empty = []

  (*  size [(k_0,v_0),...,(k_{n-1}, d_{n-1})] = n.
  *
  *  You must replace this implementation with one that uses an appropr,67777iate
  *  list functional.
  *)
  fun size (kvs : 'a dict) : int = 
      List.foldr (fn (_, l) => l + 1) 0 kvs
   
  

  (* member (kvs, k) = true,  k ∈ dom(kvs)
  *                    false, o/w.
  *)
  fun member (kvs : 'a dict, k : string) : bool =
    List.exists (fn (k', _) => k' = k) kvs

  (*  get ([(k_0,v_0),...,(k_{n-1}, d_{n-1})], k) = v_i, where k_i = k.
  *
  *  Raises NotFound if k ≠ k_i for any 0 ≤ i < n.
  *)
  fun get (kvs : 'a dict, k : string) : 'a =
    case kvs of
         [] => raise NotFound
       | (k',v') :: ys => if k = k' then v' else get(ys, k)

  (*  update(d, k, v) = d', where dom(d') = dom(d) ∪ {k} and
  *     get(d', k') = v,          k' = k
  *                   get(d, k'), k' ≠ k
  *  I.e., update(d, k, v) is a dictionary that is the same as d, except
  *  that the key-value pair (k, v) is added to it (overwriting any existing
  *  key-value pair with key k).
  *
  *  There is a relatively straightforward implementation of this function
  *  that applies one functional and then another to `kvs`.  Such an
  *  implementation makes two passes through the list.  Try to come up with
  *  a single-pass implementation that uses `foldr`.  To do this, you need
  *  to think of a direct implementation in which the value for the cons
  *  case does not depend directly on the tail.
  *)
  fun update (kvs : 'a dict, k : string, v : 'a) : 'a dict =
    (k, v) :: List.foldr 
      (fn ((k', v'), newd) => if k' = k then (k, v) :: newd  
      else (k', v') :: newd) [] (List.filter (fn (k', _) => k' <> k)  kvs)

  (*  updateVal (d, k, f) = d', where dom(d') = dom(d) and
  *     get(d', k') = f(get(d, k)), k' = k
  *                   get(d, k'),   k' ≠ k
  *  I.e., updateVal(d, k, f) is a dictionary that is the same as d, except
  *  that the key-value pair (k, v) is changed to (k, f v).  If there is no
  *  key-value pair with key k, then d' is the same as d.
  *)
  fun updateVal (kvs : 'a dict, k : string, f : 'a -> 'a) : 'a dict =  
      List.map (fn (k', v') => if k' = k then (k', f v') else (k', v')) kvs
   

  (*  insert((k, v), [(k₀,v₀),...,(k_{n-1},v_{n-1})]) =
  *     [(k₀,v₀),...,(k_{i-1},v_{i-1}),(k, v),(k_i,v_i),...,(k_{n-1},v_{n-1})]
  *     where k_{i-1} ≤ k < k_i.
  *   Pre-condition:  k₀ ≤ k₁ ≤ ... ≤ k_{n-1}.
  *
  * You are not required to reimplement this function using a list
  * functional.  But it is a nice little challenge.  The hint:  use foldr to
  * return a value f of type 'a -> 'a list such f z inserts z into xs.
  *)
  fun insert (leq : 'a*'a -> bool) (x : 'a, xs : 'a list) : 'a list =
    case xs of
         [] => [x]
       | y :: ys => if leq(x, y) then x :: xs else y :: insert leq (x, ys)

  (*  sort(kvs) = sorted(kvs), where (k, v) <= (k', v') if k <= k'.
  *
  *  This function must be an insertion sort implementation, using `insert`
  *  and an appropriate list functional.
  *)
  fun sort(kvs : (string*'a) list) : (string*'a) list =
    List.foldr (fn (kvs', sorted) => 
      insert (fn ((k1, _), (k2, _)) => k1 <= k2) (kvs', sorted)) [] kvs
    

  (*  listKvs(kvs) = sorted(kvs), where (k, v) <= (k', v') if k <= k'.
  *
  *  Do not change this definition.
  *)
  fun listKvs (kvs : 'a dict) : (string*'a) list =
    sort kvs

end

// child imports and css
import React, { useState, useEffect } from 'react';
import AddSong from './addSong';
import UpdateSong from './edit';
import DeleteSong from './delete';
import SearchSongs from './searchSong';
import axios from "axios";
import './App.css';

// App function. Holds all the functions we need for functionality
function App() {
  const [feature, setFeature] = useState('view'); // 'view', 'edit', 'delete', or 'add'
  const [songList, setSongList] = useState([]);
  const [editSong, setEditSong] = useState(null);
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [error, setError] = useState('');
  const [isLoggedIn, setIsLoggedIn] = useState(false);
  const [showRegistration, setShowRegistration] = useState(false); // Manage registration form visibility
  const [searchResults, setSearchResults] = useState([]); // Store search results

  // Fetches the initial list of songs from the server
  useEffect(() => {
    axios
      .get('http://localhost/index.php/user/view')
      .then((res) => {
        setSongList(res.data); // Update state with fetched data
      })
      .catch((error) => {
        console.error('Error fetching songs:', error);
      });
  }, []);

  // Handles the user registration (ChatGPT assisted in this)  
  const handleRegistration = async (event) => {
    event.preventDefault();
    if (!username || !password || password.length < 10) {
      setError('Please provide a valid username and a password with more than 10 characters.');
      return;
    }
    try {
      // Send a POST request to register the user. Updates states as needed
      const response = await axios.post('http://localhost/index.php/user/create', { username, password });
      if (response.status < 300 && response.data === true) {
        setError('');
        setIsLoggedIn(false);
        setShowRegistration(false);
        setFeature('view');
        setUsername('');
        setPassword('');
      } else {
        setError('Registration failed. Please try again.');
      }
    } catch (error) {
      setError('Network error. Please check your connection and try again.');
    }
  };

  // Handles logging the user in  
  const handleLogin = async (event) => {
    if (!username || !password) {
      setError('Please provide a valid username and password.');
      return;
    }
    event.preventDefault();
    try {
      // POST request. Updates states accordingly if successful 
      const response = await axios.post('http://localhost/index.php/user/check', { username, password });
      if (response.status < 300 && response.data === true) {
        setError('');
        setIsLoggedIn(true);
        setFeature('view');
      } else {
        setError('Invalid username or password.');
      }
    } catch (error) {
      setError('Network error. Please check your connection and try again.');
    }
  };

  // Handles adding a new song to the DB using axios (ChatGPT assisted in this)
  const handleAddSong = (newSong) => {
    if (!newSong.artist || !newSong.song || !newSong.rating || newSong.rating < 1 || newSong.rating > 5) {
      setError('Please fill out all fields and provide a rating between 1 and 5.');
      return;
    }  
    axios.post('http://localhost/index.php/user/add', {
      ...newSong,
      username: username
    }, {
      headers: {
        'Content-Type': 'application/json',
      },
    })
    // update states with new values
    .then((response) => {
      if (response.data!=="false"){
        const data_new = response.data; 
        setSongList(data_new);
        setFeature('view');}
      else{
        alert("The song already exists");
        setFeature('add');

      }
      
    })
    .catch((error) => {
      console.error('Error adding song:', error);
    });
};

  // Handles editing a song rating using axios   
  const handleEditSong = (editedSong) => {
    if (!editedSong.artist || !editedSong.song || !editedSong.rating || editedSong.rating < 1 || editedSong.rating > 5) {
      setError('Please fill out all fields and provide a rating between 1 and 5.');
      return;
    }
    axios.post(`http://localhost/index.php/user/update`, editedSong, {
      headers: {
        'Content-Type': 'application/json',
      },
    })
    // update states accordingly
    .then(() => {
      const updatedSongList = songList.map((song) =>
        song.id === editedSong.id ? editedSong : song
      );
      setSongList(updatedSongList);
      setFeature('view');
      setEditSong(null);
    })
    .catch((error) => {
      console.error('Error editing song:', error);
    });
  };

    // Handles deleting a song using axios 
  const handleDeleteSong = (songId) => {
    axios.post('http://localhost/index.php/user/delete', { id: songId }, {
      headers: {
        'Content-Type': 'application/json',
      },
    })
    // update states accordingly
    .then(() => {
      const updatedSongList = songList.filter((song) => song.id !== songId);
      setSongList(updatedSongList);
      setFeature('view');
    })
    .catch((error) => {
      console.error('Error deleting song:', error);
    });
  };

  // Handle search input changes
      const handleSearch = (results) => {
        if (results === '') {
          alert("Nothing found");
          return;
        }
        setSearchResults(results);
      };

  // The UI 
  return (
    <div>
    <h1>Song Rating App</h1>
    {/* Show registration and log in page first */}
    {!isLoggedIn ? (
      <div>
        {showRegistration ? (
          <div>
            <h1>Register</h1>
            <form onSubmit={handleRegistration}>
            <div>
                <label htmlFor="username">Username:</label>
                <input id="username" type="text" value={username} onChange={(e) => setUsername(e.target.value)} />
              </div>
              <div>
                <label htmlFor="password">Password:</label>
                <input id="password" type="password" value={password} onChange={(e) => setPassword(e.target.value)} />
              </div>
              <button type="submit">Register</button>
              {error && <p>{error}</p>}
            </form>
          </div>
        ) : (
          <div>
          <h1>Login</h1>
          <form onSubmit={handleLogin}>
            <div>
              <label htmlFor="loginUsername">Username:</label>
              <input id="loginUsername" type="text" value={username} onChange={(e) => setUsername(e.target.value)} />
            </div>
            <div>
              <label htmlFor="loginPassword">Password:</label>
              <input id="loginPassword" type="password" value={password} onChange={(e) => setPassword(e.target.value)} />
            </div>
            <button type="submit">Login</button>
            <button onClick={() => setShowRegistration(true)}>Register</button>
            {error && <p>{error}</p>}
          </form>
        </div>
        )}
      </div>
      )  
       : (
        // Render features when the user is logged in (StackOverflow assisted in this)    
        <div>
          <SearchSongs songList={songList} onSearch={handleSearch} />
            {searchResults.length > 0 && (
              <ul>
                {searchResults.map((song) => (
                  <li key={song.id}>
                    <strong>Artist:</strong> {song.artist}, <strong>Song:</strong> {song.song}
                  </li>
                ))}
              </ul>
            )}
          {feature === 'view' && (
            <div>
              <ul className='view-pane'>
                {songList.map((song) => (
                  <li key={song.id}>
                    <strong>Artist:</strong> {song.artist}, <strong>Song:</strong> {song.song}, <strong>Rating:</strong> {song.rating}

                     {/* conditional that will check if username for song = username of user */}
                    {username === song.username && (
                      <div>
                        <button onClick={() => { setFeature('edit'); setEditSong(song); }}>Edit</button>
                        <button onClick={() => { setFeature('delete'); setEditSong(song); }}>Delete</button>
                      </div>
                    )}
                  </li>
                ))}
              </ul>
              <button onClick={() => setFeature('add')}>Add Song</button>
              <button onClick={() => {setIsLoggedIn(false)}}>Log out</button>
            </div>
          )}

        {/* these functions will be called upon a change of state that which matches their condition */}
          <div className="edit-add-pane">
            {feature === 'add' && songList && (
              <AddSong onAddSong={handleAddSong} onCancel={() => setFeature('view')} />
            )}
          
            {feature === 'edit' && editSong && (
              <UpdateSong song={editSong} onUpdate={handleEditSong} onCancel={() => setFeature('view')} />
            )}
          </div>
  
          <div className="add-song-form-show-right">
            {feature === 'delete' && editSong && (
              <DeleteSong song={editSong} onDeleteSong={handleDeleteSong} onCancel={() => setFeature('view')} />
            )}
          </div>
        </div>
       )}
    </div>
  );
  
}

export default App;
          
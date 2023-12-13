import React, { useState } from 'react';

// AddSong component of the app
function AddSong({ onAddSong,onCancel }) {
  const [artist, setArtist] = useState('');
  const [song, setSong] = useState('');
  const [rating, setRating] = useState('');
  

  const handleAddSong = (e) => {
    e.preventDefault();

    // Check if the rating is valid
    if (rating < 0 || rating > 5) {
      alert("Rating should be between 0 and 5");
      return;
    }

    // Create a new song object with the input values
    const newSong = {
       artist,
      song,
      rating:parseInt(rating)
      
    };

    // Call the parent component's callback function to add the new song
    onAddSong(newSong);

    // Reset the form fields
    setArtist('');
    setSong('');
    setRating('');
  };

  // Handles cancel request
  const handlecancel = ()=>{
    onCancel();
  }
  return (
    <div>
      <h2>Add New Song Rating</h2>
      <form onSubmit={handleAddSong}>
        <div>
          <label>Artist:</label>
          <input type="text" value={artist} onChange={(e) => setArtist(e.target.value)} />
        </div>
        <div>
          <label>Song:</label>
          <input type="text" value={song} onChange={(e) => setSong(e.target.value)} />
        </div>
        <div>
          <label>Rating:</label>
          <input type="number" value={rating} onChange={(e) => setRating(e.target.value)} />
        </div>
        <button type="submit">
          Add Song
        </button>
        <button onClick={handlecancel}>Cancel</button>
      </form>
    </div>
  );
}

export default AddSong;
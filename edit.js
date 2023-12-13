import React, { useState } from 'react';

// Update song component for App.js. 
function UpdateSong({ song: initialSong, onUpdate,onCancel }) {
  const [song, setTitle] = useState(initialSong.song);
  const [artist, setArtist] = useState(initialSong.artist);
  const [rating, setRating] = useState(initialSong.rating);

  const handleEditSong = () => {
    // Update the song object with the new properties
    const updatedSong = { ...initialSong, song, artist, rating: parseInt(rating) };
    if (rating < 0 || rating > 5) {
      alert("Rating should be between 0 and 5");
      return;
    }

    // Call the parent component's callback function to edit the song
    onUpdate(updatedSong);
  };

  // Handles cancel request
  const handlecancel = ()=>{
    onCancel();
  }

  return (
    <div>
      <h2>Edit Song</h2>
      <p>
        Artist: {initialSong.artist}, Song Title: {initialSong.song}, Current Rating: {initialSong.rating}
      </p>
      <form onSubmit={e => e.preventDefault()}> {/* Prevent default form submission */}
        <div>
          <label>New Title:</label>
          <input type="text" value={song} onChange={(e) => setTitle(e.target.value)} /> 
          <br />
          
          <label>New Artist:</label>
          <input type="text" value={artist} onChange={(e) => setArtist(e.target.value)} />
          <br/>
          <label>New Rating:</label>
          <input type="number" value={rating} onChange={(e) => setRating(e.target.value)} />
          <br />
        </div>
        <button type="button" onClick={handleEditSong}>
          Update Song
        </button>
        <button type="button" onClick={handlecancel}>
          Cancel
        </button>
      </form>
    </div>
  );
}

export default UpdateSong;
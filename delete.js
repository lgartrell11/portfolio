import React from 'react';

// Delete component for App.js
function DeleteSong({ song, onDeleteSong,onCancel }) {
    const handleDeleteSong = () => {
      // Send the song ID to the parent component (App.js) for deletion
      onDeleteSong(song.id);
    };

    // handles cancel request
    const handlecancel = ()=>{
      onCancel();
    }

    return (
      <div>
        <h2>Delete Song</h2>
        <p>Are you sure you want to delete the song "{song.song}"?</p>
        <button onClick={handleDeleteSong}>Delete</button>
        <button onClick={handlecancel}>Cancel</button>
        
      </div>
    );
  }
  
  export default DeleteSong;
import React, { useState } from 'react';

// Search song conponent for App.js
const SearchSongs = ({ songList, onSearch }) => {
  const [searchInput, setSearchInput] = useState('');

  const handleSearchInput = () => {
    // Use the searchInput state variable to filter the songs
    const filtered = songList.filter((song) =>
    song.artist.toLowerCase() === searchInput.toLowerCase().trim() // trim to remove whitespace
  );
    onSearch(filtered); // Pass the filtered list back to the parent component
  };

  return (
    <div>
      <label>Artist:</label>
      <input
        type="text"
        value={searchInput}
        onChange={(e) => setSearchInput(e.target.value)}
      />
      <button onClick={handleSearchInput}>Search</button>
    </div>
  );
};

export default SearchSongs;

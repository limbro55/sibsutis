import React from 'react';

function SearchAndSort({ value, onChange, sortBy, onSortByChange, sortOrder, onSortOrderChange }) {
  return (
    <div>
      <input
        type="text"
        placeholder="Search by title or author..."
        value={value}
        onChange={onChange}
      />
      <select value={sortBy} onChange={onSortByChange}>
        <option value="title">Title</option>
        <option value="authors">Author</option>
      </select>
      <select value={sortOrder} onChange={onSortOrderChange}>
        <option value="asc">Ascending</option>
        <option value="desc">Descending</option>
      </select>
    </div>
  );
}

export default SearchAndSort;
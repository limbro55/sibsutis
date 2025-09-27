import { useState, useEffect } from 'react';
import logo from './assets/Notitlebookmin.jpg';
import './App.css';
import Book from './BookCard.jsx';
import SearchAndSort from './SearchAndSort.jsx';

function App() {
  const [books, setBooks] = useState([]);
  const [value, setValue] = useState('');
  const [sortBy, setSortBy] = useState('title'); // По умолчанию сортируем по названию
  const [sortOrder, setSortOrder] = useState('asc'); // По умолчанию сортируем по возрастанию

  useEffect(() => {
    fetch('https://fakeapi.extendsclass.com/books')
      .then((response) => response.json())
      .then((data) => {
        setBooks(data);

        data.forEach((book, index) => {
          setTimeout(() => {
            fetchBookCover(book);
          }, index * 1000);
        });
      });
  }, []);

  const fetchBookCover = (book) => {
    fetch(`https://www.googleapis.com/books/v1/volumes?q=isbn:${book.isbn}`)
      .then((response) => response.json())
      .then((googleData) => {
        const thumbnail = googleData.items?.[0]?.volumeInfo?.imageLinks?.thumbnail;

        setBooks((prevBooks) =>
          prevBooks.map((b) =>
            b.id === book.id
              ? { ...b, thumbnailUrl: thumbnail || logo }
              : b
          )
        );
      })
      .catch((error) => {
        console.error('Ошибка при запросе обложки:', error);
        setBooks((prevBooks) =>
          prevBooks.map((b) =>
            b.id === book.id ? { ...b, thumbnailUrl: logo } : b
          )
        );
      });
  };

  const filteredBooks = books.filter((book) => {
    const searchValue = value.toLowerCase();
    const titleMatch = book.title.toLowerCase().includes(searchValue);
    const authorMatch = book.authors
      ? book.authors.join(', ').toLowerCase().includes(searchValue)
      : false;
    return titleMatch || authorMatch;
  });

  const sortedBooks = filteredBooks.sort((a, b) => {
    let aValue, bValue;

    if (sortBy === 'title') {
      aValue = a.title || '';
      bValue = b.title || '';
    } else if (sortBy === 'authors') {
      aValue = a.authors ? a.authors.join(', ') : '';
      bValue = b.authors ? b.authors.join(', ') : '';
    }

    if (sortOrder === 'asc') {
      return aValue.localeCompare(bValue);
    } else {
      return bValue.localeCompare(aValue);
    }
  });

  return (
    <>
      <SearchAndSort
        value={value}
        onChange={(event) => setValue(event.target.value)}
        sortBy={sortBy}
        onSortByChange={(event) => setSortBy(event.target.value)}
        sortOrder={sortOrder}
        onSortOrderChange={(event) => setSortOrder(event.target.value)}
      />
      <div className="App">
        {sortedBooks.map((book) => (
          <Book
            key={book.id}
            title={book.title}
            author={book.authors ? book.authors.join(', ') : 'Unknown Author'}
            image={book.thumbnailUrl}
          />
        ))}
      </div>
    </>
  );
}

export default App;
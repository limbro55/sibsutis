import './BookCard.css';

function Book(props){
    const {title, author, image} = props;
    return(
        <div>
        <div className="book-card">
        <img src={image} alt={title} className="book-image" />
          <h2>{title}</h2>
          <p>{author}</p>
        </div>
      </div>
    );
}

export default Book
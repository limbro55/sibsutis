import React from "react";
import PersonComponent from "./PersonComponent";

function ListPage({ people }) {
  return (
    <div>
      <h2>Список людей</h2>
      {people.length === 0 ? (
        <p>Нет добавленных людей.</p>
      ) : (
        people.map((p, index) => <PersonComponent key={index} person={p} />)
      )}
    </div>
  );
}

export default ListPage;

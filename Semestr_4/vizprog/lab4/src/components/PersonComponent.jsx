import React from "react";

function PersonComponent({ person }) {
  return (
    <div style={{ border: "1px solid #ccc", padding: 10, marginBottom: 10 }}>
      <p><strong>Имя:</strong> {person.name}</p>
      <p><strong>Возраст:</strong> {person.age}</p>
      <p><strong>Email:</strong> {person.email}</p>
      <div>
        <strong>Питомцы:</strong>
        <ul>
          {person.pet.map((p, idx) => (
            <li key={idx}>{p.name} ({p.age} лет)</li>
          ))}
        </ul>
      </div>
    </div>
  );
}

export default PersonComponent;

import React, { useState } from 'react';

const Accordion = ({ header, children, renderHeader }) => {
  const [isOpen, setIsOpen] = useState(false);

  const toggleAccordion = () => setIsOpen(!isOpen);

  return (
    <div style={{ margin: '10px', borderRadius: '5px' }}>
      <div
        style={{
          padding: '10px',
          cursor: 'pointer',
          backgroundColor: '#f5f5f5',
          display: 'flex',
          alignItems: 'center',
          border: '1px solid #ccc',
          borderRadius: '5px'
        }}
        onClick={toggleAccordion}
      >
        {renderHeader ? renderHeader(header, isOpen) : header}
      </div>
      <div
        style={{
          padding: isOpen ? '10px' : '0',
          border: isOpen ? '1px solid #ccc' : 'none',
          borderTop: 'none',
          transition: 'height 0.3s ease',
          overflow: 'hidden',
          height: isOpen ? 'auto' : '0',
        }}
      >
        {isOpen && children}
      </div>
    </div>
  );
};

export default Accordion;

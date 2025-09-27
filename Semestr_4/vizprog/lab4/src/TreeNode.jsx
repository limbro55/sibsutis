import React, { useState } from 'react';

const TreeNode = ({ node, renderHeader, renderChildren, disableInteraction = false }) => {
  const [isOpen, setIsOpen] = useState(false);

  const isLeaf = node.children == null;

  const toggle = () => {
    if (!isLeaf && !disableInteraction) setIsOpen(!isOpen);
  };

  return (
    <div style={{ marginLeft: '20px' }}>
      <div
        onClick={toggle}
        style={{
          cursor: isLeaf || disableInteraction ? 'default' : 'pointer',
          backgroundColor: '#f5f5f5',
          border: '1px solid #ccc',
          borderRadius: '4px',
          padding: '8px',
          display: 'flex',
          alignItems: 'center',
        }}
      >
        {renderHeader ? renderHeader(node.header, isOpen, isLeaf) : node.header}
      </div>

      {!isLeaf && (disableInteraction || isOpen) && (
        <div style={{ marginTop: '4px', marginLeft: '16px' }}>
          {renderChildren
            ? renderChildren(node.children)
            : node.children.map((child, idx) => (
                <TreeNode
                  key={idx}
                  node={child}
                  renderHeader={renderHeader}
                  renderChildren={renderChildren}
                  disableInteraction={disableInteraction}
                />
              ))}
        </div>
      )}
    </div>
  );
};

export default TreeNode;
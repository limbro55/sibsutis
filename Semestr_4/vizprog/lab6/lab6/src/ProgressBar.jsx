import React from 'react';
import styles from './ProgressBar.module.css';

const ProgressBar = ({ title, percentage, onCancel }) => {
  const isCanceled = percentage === null;

  return (
    <div className={styles.container}>
      <h3 className={styles.title}>{title}</h3>
      {isCanceled ? (
        <p className={styles.canceled}>Canceled</p>
      ) : (
        <div className={styles.progressBar}>
          <div
            className={styles.progress}
            style={{ width: `${percentage}%` }}
          >
            {percentage}%
          </div>
        </div>
      )}
      <button
        className={styles.button}
        onClick={onCancel}
        disabled={isCanceled}
      >
        Cancel
      </button>
    </div>
  );
};

export default ProgressBar;
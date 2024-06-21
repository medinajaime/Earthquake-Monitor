import React from 'react';
import MonitorControl from './components/MonitorControl';
import EarthquakeLogs from './components/EarthquakeLogs';
import './App.css';

function App() {
  return (
      <div className="App">
        <header className="App-header">
          <h1>Earthquake Monitor</h1>
          <MonitorControl />
          <EarthquakeLogs />
        </header>
      </div>
  );
}

export default App;

import React, { useEffect, useState } from 'react';
import MonitorControl from './components/MonitorControl';
import EarthquakeLogs from './components/EarthquakeLogs';
import './App.css';

function App() {
    const [earthquakeData, setEarthquakeData] = useState([]);

    useEffect(() => {
        const ws = new WebSocket('ws://localhost:8080/ws');

        ws.onopen = () => {
            console.log('Connected to WebSocket');
        };

        ws.onmessage = (event) => {
            const data = JSON.parse(event.data);
            setEarthquakeData((prevData) => [...prevData, data]);
        };

        ws.onclose = () => {
            console.log('Disconnected from WebSocket');
        };

        return () => {
            ws.close();
        };
    }, []);

    return (
        <div className="App">
            <header className="App-header">
                <h1>Earthquake Monitor</h1>
                <MonitorControl />
                <EarthquakeLogs data={earthquakeData} />
            </header>
        </div>
    );
}

export default App;

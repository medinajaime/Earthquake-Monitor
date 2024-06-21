import React from 'react';
import axios from 'axios';

class EarthquakeLogs extends React.Component {
    state = {
        logs: ''
    };

    fetchLogs = async () => {
        try {
            const response = await axios.get('http://localhost:8080/earthquakes');
            this.setState({ logs: response.data });
        } catch (error) {
            console.error('There was an error fetching the logs!', error);
        }
    };

    componentDidMount() {
        this.fetchLogs();
        this.interval = setInterval(this.fetchLogs, 60000); // Fetch logs every minute

        this.ws = new WebSocket('ws://localhost:8080/ws');
        this.ws.onopen = () => {
            console.log('Connected to WebSocket');
        };
        this.ws.onmessage = (event) => {
            const data = JSON.parse(event.data);
            this.setState((prevState) => ({
                logs: prevState.logs ? `${prevState.logs}\n${data}` : data
            }));
        };
        this.ws.onclose = () => {
            console.log('Disconnected from WebSocket');
        };
    }

    componentWillUnmount() {
        clearInterval(this.interval);
        this.ws.close();
    }

    render() {
        return (
            <div>
                <h2>Earthquake Logs</h2>
                <pre>{this.state.logs}</pre>
            </div>
        );
    }
}

export default EarthquakeLogs;

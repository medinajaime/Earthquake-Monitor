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
    }

    componentWillUnmount() {
        clearInterval(this.interval);
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

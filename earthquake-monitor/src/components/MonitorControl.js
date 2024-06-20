import React from 'react';
import axios from 'axios';

class MonitorControl extends React.Component {
    startMonitoring = async () => {
        try {
            const response = await axios.post('http://localhost:8080/start-monitoring');
            alert(response.data);
        } catch (error) {
            console.error('There was an error starting the monitoring!', error);
        }
    };

    stopMonitoring = async () => {
        try {
            const response = await axios.post('http://localhost:8080/stop-monitoring');
            alert(response.data);
        } catch (error) {
            console.error('There was an error stopping the monitoring!', error);
        }
    };

    render() {
        return (
            <div>
                <button onClick={this.startMonitoring}>Start Monitoring</button>
                <button onClick={this.stopMonitoring}>Stop Monitoring</button>
            </div>
        );
    }
}

export default MonitorControl;

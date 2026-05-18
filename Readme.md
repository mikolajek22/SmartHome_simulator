
# IoT Weather Simulator

## Description

IoT Weather Simulator is a C++ and Python based project that simulates environmental IoT telemetry data and visualizes it using a realtime Streamlit dashboard.

The simulator generates realistic weather conditions including:

- temperature
- humidity
- atmospheric pressure
- sunlight intensity
- rainfall
- soil humidity
- air quality

The generated data is stored inside an SQLite database and analyzed through an interactive dashboard.

The system supports both:

- historical simulation
- realtime live simulation

Historical data is generated from January 1st 2025 up to the current date.  
After historical generation finishes, the simulator switches into realtime mode where:

1 second = 1 simulated hour

```text
sqlite3 iot.db < init.sql

mkdir build
cd build
cmake ..
make
./iot_sim_app
cd ..


conda activate <your_environment_name>

req.yml

streamlit run app.py
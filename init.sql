CREATE TABLE IF NOT EXISTS devices (
    id INTEGER PRIMARY KEY AUTOINCREMENT,

    type TEXT NOT NULL,
    location TEXT NOT NULL,

    mac TEXT NOT NULL,
    ip TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS weather_data (
    id INTEGER PRIMARY KEY AUTOINCREMENT,

    timestamp TEXT NOT NULL,

    temperature REAL,
    air_quality REAL,
    pressure REAL,
    humidity REAL,
    light REAL,

    rain INTEGER,
    rain_intensity REAL,

    soil_humidity REAL
);

INSERT INTO devices(type, location, mac, ip)
VALUES
('weather_station', 'outdoor', '10:20:30:40:50:01', '192.168.0.2');
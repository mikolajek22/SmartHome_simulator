import sqlite3
import pandas as pd
import streamlit as st
import matplotlib.pyplot as plt
from streamlit_autorefresh import st_autorefresh
import os

BASE_DIR = os.path.dirname(__file__)
DB_PATH = os.path.join(BASE_DIR, "iot.db")

st.set_page_config(
    page_title="IoT Weather Dashboard",
    layout="wide"
)

# =========================
# Sidebar controls
# =========================

st.sidebar.header("Realtime Settings")

live_refresh = st.sidebar.toggle(
    "Enable live refresh",
    value=False
)

refresh_rate = st.sidebar.slider(
    "Refresh interval [ms]",
    min_value=500,
    max_value=10000,
    value=1000,
    step=500
)

if live_refresh:
    st_autorefresh(
        interval=refresh_rate,
        key="realtime_refresh"
    )


@st.cache_data(ttl=1)
def load_data(limit=5000):

    conn = sqlite3.connect(DB_PATH)

    query = f"""
    SELECT *
    FROM weather_data
    ORDER BY timestamp DESC
    LIMIT {limit}
    """

    df = pd.read_sql_query(query, conn)

    conn.close()

    df["timestamp"] = pd.to_datetime(df["timestamp"])

    df = df.sort_values(by="timestamp")

    return df


# Load database
try:
    df = load_data(limit=10000)

except Exception as e:
    st.error(f"Database error: {e}")
    st.stop()


st.title("IoT Weather Simulator Dashboard")

st.markdown("### Historical and realtime weather simulation")

if live_refresh:
    st.success(f"Live refresh enabled ({refresh_rate} ms)")
else:
    st.info("Live refresh disabled - showing latest saved data")


# =========================
# Latest values
# =========================

latest = df.iloc[-1]

col1, col2, col3, col4, col5 = st.columns(5)

with col1:
    st.metric(
        label="Temperature",
        value=f"{latest['temperature']:.2f} °C"
    )

with col2:
    st.metric(
        label="Humidity",
        value=f"{latest['humidity']:.2f} %"
    )

with col3:
    st.metric(
        label="Pressure",
        value=f"{latest['pressure']:.2f} hPa"
    )

with col4:
    st.metric(
        label="Light",
        value=f"{latest['light']:.2f}"
    )

with col5:
    st.metric(
        label="Air Quality",
        value=f"{latest['air_quality']:.2f}"
    )

st.divider()

# =========================
# Historical range selector
# =========================

st.sidebar.header("Data Filters")

min_date = df["timestamp"].min().to_pydatetime()
max_date = df["timestamp"].max().to_pydatetime()

selected_range = st.sidebar.slider(
    "Select date range",
    min_value=min_date,
    max_value=max_date,
    value=(max_date - pd.Timedelta(days=7), max_date),
    format="YYYY/MM/DD HH:mm"
)

st.sidebar.markdown("### Manual date input")

manual_start_date = st.sidebar.text_input(
    "Start date [YYYY-MM-DD HH:MM]",
    value=(max_date - pd.Timedelta(days=7)).strftime("%Y-%m-%d %H:%M")
)

manual_end_date = st.sidebar.text_input(
    "End date [YYYY-MM-DD HH:MM]",
    value=max_date.strftime("%Y-%m-%d %H:%M")
)

use_manual_dates = st.sidebar.toggle(
    "Use manual date input",
    value=False
)

if use_manual_dates:

    try:
        start_date = pd.to_datetime(manual_start_date)
        end_date = pd.to_datetime(manual_end_date)

    except Exception:

        st.sidebar.error("Invalid date format")

        start_date, end_date = selected_range

else:

    start_date, end_date = selected_range

filtered_df = df[
    (df["timestamp"] >= start_date) &
    (df["timestamp"] <= end_date)
]


# =========================
# Temperature chart
# =========================

st.header("Temperature")

temp_chart_mode = st.selectbox(
    "Temperature chart mode",
    [
        "Raw temperature",
        "Average by hour",
        "Average by day",
        "Average by month",
        "Min/Max by month"
    ]
)

fig1, ax1 = plt.subplots(figsize=(12, 4))

if temp_chart_mode == "Raw temperature":

    ax1.plot(
        filtered_df["timestamp"],
        filtered_df["temperature"]
    )

    ax1.set_xlabel("Time")

elif temp_chart_mode == "Average by hour":

    hourly = (
        filtered_df
        .groupby(filtered_df["timestamp"].dt.hour)["temperature"]
        .mean()
    )

    ax1.plot(hourly.index, hourly.values)

    ax1.set_xlabel("Hour")

elif temp_chart_mode == "Average by day":

    daily = (
        filtered_df
        .groupby(filtered_df["timestamp"].dt.date)["temperature"]
        .mean()
    )

    ax1.plot(daily.index, daily.values)

    ax1.set_xlabel("Day")

elif temp_chart_mode == "Average by month":

    monthly = (
        filtered_df
        .groupby(filtered_df["timestamp"].dt.month)["temperature"]
        .mean()
    )

    ax1.bar(monthly.index, monthly.values)

    ax1.set_xlabel("Month")

elif temp_chart_mode == "Min/Max by month":

    monthly = (
        filtered_df
        .groupby(filtered_df["timestamp"].dt.month)["temperature"]
        .agg(["min", "max"])
    )

    ax1.plot(monthly.index, monthly["min"], label="Min")
    ax1.plot(monthly.index, monthly["max"], label="Max")

    ax1.legend()

    ax1.set_xlabel("Month")

ax1.set_ylabel("Temperature [°C]")
ax1.grid(True)

st.pyplot(fig1)


# =========================
# Humidity chart
# =========================

st.header("Humidity")

humidity_chart_mode = st.selectbox(
    "Humidity chart mode",
    [
        "Raw humidity",
        "Average by hour",
        "Average by day",
        "Average by month"
    ]
)

fig2, ax2 = plt.subplots(figsize=(12, 4))

if humidity_chart_mode == "Raw humidity":

    ax2.plot(
        filtered_df["timestamp"],
        filtered_df["humidity"]
    )

    ax2.set_xlabel("Time")

elif humidity_chart_mode == "Average by hour":

    hourly = (
        filtered_df
        .groupby(filtered_df["timestamp"].dt.hour)["humidity"]
        .mean()
    )

    ax2.plot(hourly.index, hourly.values)

    ax2.set_xlabel("Hour")

elif humidity_chart_mode == "Average by day":

    daily = (
        filtered_df
        .groupby(filtered_df["timestamp"].dt.date)["humidity"]
        .mean()
    )

    ax2.plot(daily.index, daily.values)

    ax2.set_xlabel("Day")

elif humidity_chart_mode == "Average by month":

    monthly = (
        filtered_df
        .groupby(filtered_df["timestamp"].dt.month)["humidity"]
        .mean()
    )

    ax2.bar(monthly.index, monthly.values)

    ax2.set_xlabel("Month")

ax2.set_ylabel("Humidity [%]")
ax2.grid(True)

st.pyplot(fig2)


# =========================
# Pressure chart
# =========================

st.header("Pressure")

fig3, ax3 = plt.subplots(figsize=(12, 4))

ax3.plot(
    filtered_df["timestamp"],
    filtered_df["pressure"]
)

ax3.set_xlabel("Time")
ax3.set_ylabel("Pressure [hPa]")
ax3.grid(True)

st.pyplot(fig3)


# =========================
# Light chart
# =========================

st.header("Light")

fig4, ax4 = plt.subplots(figsize=(12, 4))

ax4.plot(
    filtered_df["timestamp"],
    filtered_df["light"]
)

ax4.set_xlabel("Time")
ax4.set_ylabel("Light")
ax4.grid(True)

st.pyplot(fig4)


# =========================
# Soil humidity chart
# =========================

st.header("Soil Humidity")

fig5, ax5 = plt.subplots(figsize=(12, 4))

ax5.plot(
    filtered_df["timestamp"],
    filtered_df["soil_humidity"]
)

ax5.set_xlabel("Time")
ax5.set_ylabel("Soil Humidity [%]")
ax5.grid(True)

st.pyplot(fig5)


# =========================
# Rain intensity chart
# =========================

st.header("Rain Intensity")

rain_df = filtered_df[filtered_df["rain"] == 1]

fig6, ax6 = plt.subplots(figsize=(12, 4))

ax6.plot(
    rain_df["timestamp"],
    rain_df["rain_intensity"]
)

ax6.set_xlabel("Time")
ax6.set_ylabel("Rain Intensity")
ax6.grid(True)

st.pyplot(fig6)


# =========================
# SQL Analytics Section
# =========================

st.header("SQL Analytics")

analysis_option = st.selectbox(
    "Select SQL analysis",
    [
        "Average temperature by month",
        "Average temperature by hour",
        "Average humidity by month",
        "Average pressure by month",
        "Top 10 hottest days",
        "Top 10 coldest days",
        "Most rainy days",
        "Average daylight by month",
        "Temperature statistics",
        "Rain statistics",
        "Daily temperature amplitude",
        "Longest rain period",
        "Heatwave detection",
        "Frost detection",
        "Air quality alerts",
        "Monthly min/max temperatures",
        "Day vs night temperature",
        "Average weather by weekday",
        "Environmental correlation"
    ]
)

if analysis_option == "Average temperature by month":

    result = (
        df
        .groupby(df["timestamp"].dt.month)["temperature"]
        .mean()
        .reset_index()
    )

    result.columns = ["Month", "Average Temperature"]

    st.dataframe(result)


elif analysis_option == "Average temperature by hour":

    result = (
        df
        .groupby(df["timestamp"].dt.hour)["temperature"]
        .mean()
        .reset_index()
    )

    result.columns = ["Hour", "Average Temperature"]

    st.dataframe(result)


elif analysis_option == "Average humidity by month":

    result = (
        df
        .groupby(df["timestamp"].dt.month)["humidity"]
        .mean()
        .reset_index()
    )

    result.columns = ["Month", "Average Humidity"]

    st.dataframe(result)


elif analysis_option == "Average pressure by month":

    result = (
        df
        .groupby(df["timestamp"].dt.month)["pressure"]
        .mean()
        .reset_index()
    )

    result.columns = ["Month", "Average Pressure"]

    st.dataframe(result)


elif analysis_option == "Top 10 hottest days":

    hottest = (
        df
        .groupby(df["timestamp"].dt.date)["temperature"]
        .max()
        .sort_values(ascending=False)
        .head(10)
        .reset_index()
    )

    hottest.columns = ["Date", "Max Temperature"]

    st.dataframe(hottest)


elif analysis_option == "Top 10 coldest days":

    coldest = (
        df
        .groupby(df["timestamp"].dt.date)["temperature"]
        .min()
        .sort_values(ascending=True)
        .head(10)
        .reset_index()
    )

    coldest.columns = ["Date", "Min Temperature"]

    st.dataframe(coldest)


elif analysis_option == "Most rainy days":

    rainy = (
        df
        .groupby(df["timestamp"].dt.date)["rain_intensity"]
        .sum()
        .sort_values(ascending=False)
        .head(10)
        .reset_index()
    )

    rainy.columns = ["Date", "Total Rain Intensity"]

    st.dataframe(rainy)


elif analysis_option == "Average daylight by month":

    result = (
        df
        .groupby(df["timestamp"].dt.month)["light"]
        .mean()
        .reset_index()
    )

    result.columns = ["Month", "Average Light"]

    st.dataframe(result)


elif analysis_option == "Temperature statistics":

    stats = {
        "Average Temperature": df["temperature"].mean(),
        "Minimum Temperature": df["temperature"].min(),
        "Maximum Temperature": df["temperature"].max(),
        "Temperature Std Dev": df["temperature"].std()
    }

    stats_df = pd.DataFrame(
        stats.items(),
        columns=["Statistic", "Value"]
    )

    st.dataframe(stats_df)


elif analysis_option == "Rain statistics":

    stats = {
        "Rain Hours": int(df["rain"].sum()),
        "Average Rain Intensity": df["rain_intensity"].mean(),
        "Maximum Rain Intensity": df["rain_intensity"].max()
    }

    stats_df = pd.DataFrame(
        stats.items(),
        columns=["Statistic", "Value"]
    )

    st.dataframe(stats_df)


elif analysis_option == "Daily temperature amplitude":

    amplitude = (
        df
        .groupby(df["timestamp"].dt.date)["temperature"]
        .agg(lambda x: x.max() - x.min())
        .reset_index()
    )

    amplitude.columns = ["Date", "Temperature Amplitude"]

    st.dataframe(amplitude.sort_values(
        by="Temperature Amplitude",
        ascending=False
    ).head(20))


elif analysis_option == "Longest rain period":

    rain_periods = []

    current = 0

    for value in df["rain"]:

        if value == 1:
            current += 1
        else:
            if current > 0:
                rain_periods.append(current)
            current = 0

    if len(rain_periods) > 0:

        st.metric(
            "Longest rain period [hours]",
            max(rain_periods)
        )


elif analysis_option == "Heatwave detection":

    heatwaves = df[df["temperature"] > 28.0]

    st.dataframe(
        heatwaves[[
            "timestamp",
            "temperature",
            "humidity"
        ]].tail(100)
    )


elif analysis_option == "Frost detection":

    frost = df[df["temperature"] < 0.0]

    st.metric(
        "Frost hours",
        len(frost)
    )

    st.dataframe(
        frost[[
            "timestamp",
            "temperature"
        ]].tail(100)
    )


elif analysis_option == "Air quality alerts":

    alerts = df[df["air_quality"] > 80]

    st.metric(
        "Air quality alerts",
        len(alerts)
    )

    st.dataframe(
        alerts[[
            "timestamp",
            "air_quality",
            "humidity"
        ]].tail(100)
    )


elif analysis_option == "Monthly min/max temperatures":

    result = (
        df
        .groupby(df["timestamp"].dt.month)["temperature"]
        .agg(["min", "max", "mean"])
        .reset_index()
    )

    result.columns = [
        "Month",
        "Min Temperature",
        "Max Temperature",
        "Average Temperature"
    ]

    st.dataframe(result)


elif analysis_option == "Day vs night temperature":

    day = df[
        (df["timestamp"].dt.hour >= 6) &
        (df["timestamp"].dt.hour <= 18)
    ]

    night = df[
        (df["timestamp"].dt.hour < 6) |
        (df["timestamp"].dt.hour > 18)
    ]

    comparison = pd.DataFrame({
        "Period": ["Day", "Night"],
        "Average Temperature": [
            day["temperature"].mean(),
            night["temperature"].mean()
        ]
    })

    st.dataframe(comparison)


elif analysis_option == "Average weather by weekday":

    result = (
        df
        .groupby(df["timestamp"].dt.day_name())["temperature"]
        .mean()
        .reset_index()
    )

    result.columns = ["Weekday", "Average Temperature"]

    st.dataframe(result)


elif analysis_option == "Environmental correlation":

    corr = df[[
        "temperature",
        "humidity",
        "pressure",
        "light",
        "soil_humidity",
        "air_quality"
    ]].corr()

    st.dataframe(corr)


# =========================
# Sorting and Filtering
# =========================

st.header("Advanced Sorting")

sort_column = st.selectbox(
    "Sort by",
    [
        "temperature",
        "humidity",
        "pressure",
        "light",
        "rain_intensity",
        "soil_humidity",
        "air_quality"
    ]
)

sort_order = st.radio(
    "Sort order",
    ["Descending", "Ascending"]
)

ascending = sort_order == "Ascending"

sorted_df = filtered_df.sort_values(
    by=sort_column,
    ascending=ascending
)

st.dataframe(sorted_df.head(100))


# =========================
# Raw latest data
# =========================

st.header("Latest Data")

st.dataframe(filtered_df.tail(100))
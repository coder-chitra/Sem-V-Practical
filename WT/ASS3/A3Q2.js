function updateTime() {
    const now = new Date();
    const timeString = now.toLocaleTimeString();
    document.getElementById('timeDisplay').value = timeString;
}

// Update time on page load
updateTime();

// Update time every second
setInterval(updateTime, 1000);


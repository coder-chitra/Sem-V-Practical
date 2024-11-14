function displayMessage() {
    const message = "Good Afternoon";
    document.getElementById('greetingMessage').textContent = message;
}

// Set the function to run when the page loads
window.onload = displayMessage;


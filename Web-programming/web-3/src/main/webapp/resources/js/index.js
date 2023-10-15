$(function () {
    // Delay in milliseconds between updating the date and time
    const DELAY = 10000;

    function setDate(date) {
        // Get the day, month as a string and pad it with a leading 0 if needed
        const day = date.getDate().toString().padStart(2, '0');
        // Month is 0-indexed, so we add 1
        const month = (date.getMonth() + 1).toString().padStart(2, '0');
        const year = date.getFullYear();
        $('.date').html(`${day}.${month}.${year}`);
    }

    function setTime(date) {
        // Get the hours, minutes, seconds as a string and pad it with a leading 0 if needed
        let hours = date.getHours().toString().padStart(2, '0');
        let minutes = date.getMinutes().toString().padStart(2, '0');
        let seconds = date.getSeconds().toString().padStart(2, '0');
        $('.time').html(`${hours}:${minutes}:${seconds}`);
    }

    function setCurrentDateTime() {
        // Create a new Date object for the current time
        let date = new Date();
        setDate(date);
        setTime(date);
    }

    // Set the date and time elements initially
    setCurrentDateTime();
    // Set an interval to update the date and time every DELAY milliseconds
    setInterval(setCurrentDateTime, DELAY);
});
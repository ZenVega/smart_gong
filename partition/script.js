function toggleLED() {
fetch("/toggle_led")
  .then((response) => response.text())
  .then((data) => alert(data));
}

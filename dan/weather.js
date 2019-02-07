window.onload = () => {
	let xhr = new XMLHttpRequest();
	// Request to open weather map
	// Arlington - id=4671240
	// Fort Worth - id=4691930
	// Burleson - id=4677551
	xhr.open('GET', 'http://api.openweathermap.org/data/2.5/weather?id=4671240&units=imperial&appid=bb617c8eebae0d1c79c479dd6ad0aab3');
	xhr.onload = () => {
		if (xhr.readyState === 4) {
			if (xhr.status === 200) {
				let json = JSON.parse(xhr.responseText);
				console.log(json);
				document.getElementById("temp").innerHTML = json.main.temp.toFixed(0) + "°F";
				document.getElementById("weather-description").innerHTML = json.weather[0].description;
				document.getElementById("humidity").innerHTML = json.main.humidity.toFixed(2) + "%";
				document.getElementById("name").innerHTML = json.name;
			} else {
				console.log('error msg: ' + xhr.status);
			}
		}
	}
	xhr.send();
}
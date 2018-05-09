window.onload = () => {
	let xhr = new XMLHttpRequest();
	// Request to open weather map
	xhr.open('GET', 'http://api.openweathermap.org/data/2.5/weather?id=4671240&units=imperial&appid=bb617c8eebae0d1c79c479dd6ad0aab3');
	xhr.onload = () => {
		if (xhr.readyState === 4) {
			if (xhr.status === 200) {
				let json = JSON.parse(xhr.responseText);
				console.log(json);
				document.getElementById("temp").innerHTML = json.main.temp.toFixed(0) + " F";
				document.getElementById("weather-description").innerHTML = json.weather[0].description;
			} else {
				console.log('error msg: ' + xhr.status);
			}
		}
	}
	xhr.send();
}
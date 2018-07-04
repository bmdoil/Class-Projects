/***************
 * Name: Brent Doil
 * Date: 11/6/2016
 * CS290 - Week 6
 * weather.js  
*****************/
//API Key
var appid = "7a6db99f832df1119f88c6fe808c93c5";
document.addEventListener('DOMContentLoaded', weatherBtns);

function weatherBtns() {
    document.getElementById("submit").addEventListener("click", function (event) {
        var request = new XMLHttpRequest();
        var cityName = document.getElementById("citySubmit").value;
        var zipCode = document.getElementById("zipSubmit").value;
       
        if (zipCode != "" && cityName != "")
        {
            alert("Please enter EITHER Zip OR City")
        }
        else if (zipCode != "") {
            request.open("GET", "http://api.openweathermap.org/data/2.5/weather?zip=" + zipCode + ",us" + "&units=imperial" + "&appid=" + appid, true);
        }
           
         else if (cityName != "") {
            request.open("GET", "http://api.openweathermap.org/data/2.5/weather?q=" + cityName + ",us" + "&units=imperial" + "&appid=" + appid, true);
        } else {
            alert("No zip code or no city name");
        }
        request.addEventListener("load", function () {
            if (request.status >= 200 && request.status < 400) {
                var response = JSON.parse(request.responseText);
                document.getElementById("cityName").textContent = response.name;
                document.getElementById("countryName").textContent = response.sys.country;
                
                //Make date something readable
                var date = new Date(response.dt * 1000);
                document.getElementById("dt").textContent = date;             
                document.getElementById("temp").textContent = response.main.temp;                
                document.getElementById("hum").textContent = response.main.humidity;
                document.getElementById("windSpd").textContent = response.wind.speed;
               
                
            } else {
                console.log("Network error: " + request.statusText);
            }
        });
        request.send(null);
        event.preventDefault();
    })
    
}
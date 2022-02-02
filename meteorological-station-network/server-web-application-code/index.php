<!DOCTYPE html>
<?php
$url=$_SERVER['REQUEST_URI'];
#header("Refresh: 15; URL=$url"); // Refresh the webpage every 5 seconds
?>
<html lang="en">
<title>Weather Network</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Lato">
<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Montserrat">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
<style>
body,h1,h2,h3,h4,h5,h6 {font-family: "Lato", sans-serif}
.w3-bar,h1,button {font-family: "Montserrat", sans-serif}
.fa-anchor,.fa-coffee {font-size:200px}
.table_titles {
padding-right: 20px;
padding-left: 20px;
color: #000;
}
.table_titles {
color: #FFF;
background-color: #000000;
}
table {
border: 2px solid #333;
}

</style>
<body>

<!-- Navbar -->
<div class="w3-top">
  <div class="w3-bar w3-white w3-card w3-left-align w3-large">
    <!--<a class="w3-bar-item w3-button w3-hide-medium w3-hide-large w3-right w3-padding-large w3-hover-white w3-large w3-red" href="javascript:void(0);" onclick="myFunction()" title="Toggle Navigation Menu"><i class="fa fa-bars"></i></a> -->
    <a href="#" class="w3-bar-item w3-button w3-padding-large w3-hover-black">Home</a>
    <a href="#SG" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-hover-black">HMMY Station</a>
    <a href="#SG" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-hover-black">Athena Station</a>
    <a href="#TG" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-hover-black">Esties Station</a>
    <a href="#TG" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-hover-black">PROKAT Station</a>
  </div>

  <!-- Navbar on small screens -->
  <div id="navDemo" class="w3-bar-block w3-white w3-hide w3-hide-large w3-hide-medium w3-large">
    <a href="#SG" class="w3-bar-item w3-button w3-padding-large">HMMY Station</a>
    <a href="#SG" class="w3-bar-item w3-button w3-padding-large">Athena Station</a>
    <a href="#TG" class="w3-bar-item w3-button w3-padding-large">Esties Station</a>
    <a href="#TG" class="w3-bar-item w3-button w3-padding-large">PROKAT Station</a>
  </div>
</div>

<!-- Header -->
<header class="w3-container w3-black w3-center" style="padding:128px 16px">
  <h1 class="w3-jumbo">THAT IS A WEATHER PAGE</h1>
  <p class="w3-xlarge">Template by w3.css and me</p>
</header>

<!-- First Grid -->
<div class="w3-row-padding w3-padding-64 w3-container">
  <div class="w3-content">

      <h1>Hello</h1>
      <h5 class="w3-padding-32">This Page was made for the demonstration of the weather data, collected by 4 arduino-weather stations.</h5>
        </div>
        <div class="w3-half w3-left-align">
<!-- weather widget start --><div id="m-booked-weather-bl250-48345"> <div class="booked-wzs-250-175 weather-customize" style="background-color:#137AE9;width:430px;" id="width3"> <div class="booked-wzs-250-175_in"> <div class="booked-wzs-250-175-data"> <div class="booked-wzs-250-175-left-img wrz-18"> </div> <div class="booked-wzs-250-175-right"> <div class="booked-wzs-day-deck"> <div class="booked-wzs-day-val"> <div class="booked-wzs-day-number"><span class="plus">+</span>18</div> <div class="booked-wzs-day-dergee"> <div class="booked-wzs-day-dergee-val">&deg;</div> <div class="booked-wzs-day-dergee-name">C</div> </div> </div> <div class="booked-wzs-day"> <div class="booked-wzs-day-d">H: <span class="plus">+</span>18&deg;</div> <div class="booked-wzs-day-n">L: <span class="plus">+</span>14&deg;</div> </div> </div> <div class="booked-wzs-250-175-info"> <div class="booked-wzs-250-175-city">Ξάνθη </div> <div class="booked-wzs-250-175-date">Κυριακή, 17 Οκτώβριος</div> <div class="booked-wzs-left"> <span class="booked-wzs-bottom-l">Πρόγνωση για 7 μέρες</span> </div> </div> </div> </div> <table cellpadding="0" cellspacing="0" class="booked-wzs-table-250"> <tr> <td>Δευ</td> <td>Τρι</td> <td>Τετ</td> <td>Πεμ</td> <td>Παρ</td> <td>Σαβ</td> </tr> <tr> <td class="week-day-ico"><div class="wrz-sml wrzs-18"></div></td> <td class="week-day-ico"><div class="wrz-sml wrzs-01"></div></td> <td class="week-day-ico"><div class="wrz-sml wrzs-06"></div></td> <td class="week-day-ico"><div class="wrz-sml wrzs-01"></div></td> <td class="week-day-ico"><div class="wrz-sml wrzs-01"></div></td> <td class="week-day-ico"><div class="wrz-sml wrzs-03"></div></td> </tr> <tr> <td class="week-day-val"><span class="plus">+</span>17&deg;</td> <td class="week-day-val"><span class="plus">+</span>18&deg;</td> <td class="week-day-val"><span class="plus">+</span>18&deg;</td> <td class="week-day-val"><span class="plus">+</span>18&deg;</td> <td class="week-day-val"><span class="plus">+</span>19&deg;</td> <td class="week-day-val"><span class="plus">+</span>20&deg;</td> </tr> <tr> <td class="week-day-val"><span class="plus">+</span>13&deg;</td> <td class="week-day-val"><span class="plus">+</span>12&deg;</td> <td class="week-day-val"><span class="plus">+</span>12&deg;</td> <td class="week-day-val"><span class="plus">+</span>11&deg;</td> <td class="week-day-val"><span class="plus">+</span>12&deg;</td> <td class="week-day-val"><span class="plus">+</span>13&deg;</td> </tr> </table> </div> </div> </div><script type="text/javascript"> var css_file=document.createElement("link"); var widgetUrl = location.href; css_file.setAttribute("rel","stylesheet"); css_file.setAttribute("type","text/css"); css_file.setAttribute("href",'https://s.bookcdn.com/css/w/booked-wzs-widget-275.css?v=0.0.1'); document.getElementsByTagName("head")[0].appendChild(css_file); function setWidgetData_48345(data) { if(typeof(data) != 'undefined' && data.results.length > 0) { for(var i = 0; i < data.results.length; ++i) { var objMainBlock = document.getElementById('m-booked-weather-bl250-48345'); if(objMainBlock !== null) { var copyBlock = document.getElementById('m-bookew-weather-copy-'+data.results[i].widget_type); objMainBlock.innerHTML = data.results[i].html_code; if(copyBlock !== null) objMainBlock.appendChild(copyBlock); } } } else { alert('data=undefined||data.results is empty'); } } var widgetSrc = "https://widgets.booked.net/weather/info?action=get_weather_info;ver=7;cityID=25664;type=3;scode=124;ltid=3457;domid=;anc_id=2538;countday=undefined;cmetric=1;wlangID=19;color=137AE9;wwidth=430;header_color=ffffff;text_color=333333;link_color=08488D;border_form=1;footer_color=ffffff;footer_text_color=333333;transparent=0;v=0.0.1";widgetSrc += ';ref=' + widgetUrl;widgetSrc += ';rand_id=48345';var weatherBookedScript = document.createElement("script"); weatherBookedScript.setAttribute("type", "text/javascript"); weatherBookedScript.src = widgetSrc; document.body.appendChild(weatherBookedScript) </script><!-- weather widget end -->
</div>

  <div class="w3-half w3-right-align">
  <img src="https://my.meteoblue.com/visimage/meteogram_onesmall_hd?look=KILOMETER_PER_HOUR%2CCELSIUS%2CMILLIMETER&apikey=5838a18e295d&temperature=C&windspeed=kmh&precipitationamount=mm&winddirection=3char&city=41.12%C2%B0%CE%92+24.89%C2%B0%CE%91&iso2=&lat=41.12260771393343&lon=24.888977059163153&asl=66&tz=Europe%2FAthens&lang=el&ts=1634494076&sig=5d92a9f42afa662fb9d72d7e763b81f7" style="border:1px outset #002e3d" width="610" height="370" border="0">
</div>



</div>

<!-- Second Grid -->
<div id="SG"> </div>
<div class="w3-row-padding  w3-padding-64 w3-container">



    <div class="w3-half w3-left-align">
	 <h1>HMMY Station</h1>
 <table border="5" cellspacing="0" cellpadding="7">
<tr>
<td class="table_titles">Date and Time</td>
<td class="table_titles">Temperature</td>
<td class="table_titles">Humidity</td>
<td class="table_titles">Brightness</td>
<td class="table_titles">Pressure</td>
</tr>
<?php
include('connection.php');
$result = mysqli_query($con,'SELECT * FROM hmmy ORDER BY id DESC LIMIT 5');
// Process every record
$oddrow = true;
while($row = mysqli_fetch_array($result))
{
if ($oddrow)
{
$css_class=' class="table_cells_odd"';
}
else
{
$css_class=' class="table_cells_even"';
}
$oddrow = !$oddrow;
echo "<tr align=center>";
echo "<td '.$css_class.'>" . $row['event'] . "</td>";
echo "<td '.$css_class.'>" . $row['DHT_temperature'] . "</td>";
echo "<td '.$css_class.'>" . $row['DHT_humidity'] . "</td>";
echo "<td '.$css_class.'>" . $row['Brightness'] . "</td>";
echo "<td '.$css_class.'>" . $row['LPS_pressure'] . "</td>";
echo "</tr>";
}

// Close the connection
mysqli_close($con);
?>

</table>
    </div>
	<div class="w3-half">
	<h1>Athena Station</h1>
	<table border="5" cellspacing="0" cellpadding="7">
<tr>
<td class="table_titles">Date and Time</td>
<td class="table_titles">Temperature</td>
<td class="table_titles">Humidity</td>
<td class="table_titles">Brightness</td>
</tr>
<?php
include('connection.php');
$result = mysqli_query($con,'SELECT * FROM athina ORDER BY id DESC LIMIT 5');
// Process every record
$oddrow = true;
while($row = mysqli_fetch_array($result))
{
if ($oddrow)
{
$css_class=' class="table_cells_odd"';
}
else
{
$css_class=' class="table_cells_even"';
}
$oddrow = !$oddrow;
echo "<tr align=center>";
echo "<td '.$css_class.'>" . $row['event'] . "</td>";
echo "<td '.$css_class.'>" . $row['DHT_temperature'] . "</td>";
echo "<td '.$css_class.'>" . $row['DHT_humidity'] . "</td>";
echo "<td '.$css_class.'>" . $row['Brightness'] . "</td>";
echo "</tr>";
}

// Close the connection
mysqli_close($con);
?>
</table>
<br><br><br><br>
	</div>


  <div class="w3-center" ><br><br><br><br>

<div ><h1>The values will reload in <span id="cnt" style="color:red;">30</span> Seconds</h1></div>
</div>
  <script>
      var counter = 30;

      // The countdown method.
      window.setInterval(function () {
          counter--;
          if (counter >= 0) {
              var span;
              span = document.getElementById("cnt");
              span.innerHTML = counter;
          }
          if (counter === 0) {
              clearInterval(counter);
          }

      }, 1000);

      window.setInterval('refresh()', 30000);

      // Refresh or reload page.
      function refresh() {
          window  .location.reload();
      }
  </script>

<!-- Third Grid -->

<div id="TG"> </div>
<div class="w3-row-padding  w3-padding-64 w3-container">



    <div class="w3-half w3-left-align">
	 <h1>Esties Station</h1>
 <table border="5" cellspacing="0" cellpadding="7">
<tr>
<td class="table_titles">Date and Time</td>
<td class="table_titles">Temperature</td>
<td class="table_titles">Humidity</td>
<td class="table_titles">Brightness</td>
</tr>
<?php
include('connection.php');
$result = mysqli_query($con,'SELECT * FROM esties ORDER BY id DESC LIMIT 5');
// Process every record
$oddrow = true;
while($row = mysqli_fetch_array($result))
{
if ($oddrow)
{
$css_class=' class="table_cells_odd"';
}
else
{
$css_class=' class="table_cells_even"';
}
$oddrow = !$oddrow;
echo "<tr align=center>";
echo "<td '.$css_class.'>" . $row['event'] . "</td>";
echo "<td '.$css_class.'>" . $row['DHT_temperature'] . "</td>";
echo "<td '.$css_class.'>" . $row['DHT_humidity'] . "</td>";
echo "<td '.$css_class.'>" . $row['Brightness'] . "</td>";
echo "</tr>";
}

// Close the connection
mysqli_close($con);
?>

</table>
    </div>
	<div class="w3-half">
	<h1>PROKAT Station</h1>
	<table border="5" cellspacing="0" cellpadding="7">
<tr>
<td class="table_titles">Date and Time</td>
<td class="table_titles">Temperature</td>
<td class="table_titles">Humidity</td>
<td class="table_titles">Brightness</td>
</tr>
<?php
include('connection.php');
$result = mysqli_query($con,'SELECT * FROM prokat ORDER BY id DESC LIMIT 5');
// Process every record
$oddrow = true;
while($row = mysqli_fetch_array($result))
{
if ($oddrow)
{
$css_class=' class="table_cells_odd"';
}
else
{
$css_class=' class="table_cells_even"';
}
$oddrow = !$oddrow;
echo "<tr align=center>";
echo "<td '.$css_class.'>" . $row['event'] . "</td>";
echo "<td '.$css_class.'>" . $row['DHT_temperature'] . "</td>";
echo "<td '.$css_class.'>" . $row['DHT_humidity'] . "</td>";
echo "<td '.$css_class.'>" . $row['Brightness'] . "</td>";
echo "</tr>";
}

// Close the connection
mysqli_close($con);
?>
</table>
	</div>

</div>





<div class="w3-container w3-black w3-center">

    <h1 class="w3-margin w3-xlarge"><img src="http://cam2.cityofxanthi.gr:1025/video4.mjpg" style="border:1px outset #002e3d" width="610" height="370" border="0"></h1>
</div>


<script>
// Used to toggle the menu on small screens when clicking on the menu button
function myFunction() {
  var x = document.getElementById("navDemo");
  if (x.className.indexOf("w3-show") == -1) {
    x.className += " w3-show";
  } else {
    x.className = x.className.replace(" w3-show", "");
  }
}
</script>

</body>
</html>

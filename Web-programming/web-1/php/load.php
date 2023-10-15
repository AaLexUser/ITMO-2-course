<?php
session_set_cookie_params(0);
session_start();
if(isset($_SESSION['data'])){
    foreach ($_SESSION['data'] as $elem){
        echo "<tr class='columns'>";
        echo "<td>" . $elem['x'] . "</td>";
        echo "<td>" . $elem['y'] . "</td>";
        echo "<td>" . $elem['r'] . "</td>";
        echo "<td>" . $elem['ishit']  . "</td>";
        echo "<td>" . $elem['currentTime']  . "</td>";
        echo "<td>" . $elem['executionTime']*1000 . "</td>";
        echo "</tr>";
    }
}
?>
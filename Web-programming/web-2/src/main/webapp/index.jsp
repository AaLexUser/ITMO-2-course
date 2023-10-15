<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>web-2</title>
    <meta charset="utf-8">
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
<header class="content">
    <table style="width: 100%">
        <tr>
            <td style="width: 30%">
                <h1>WEB LAB 2</h1>
            </td>
            <td>
                <h3 style="text-align: right">Lapin Alexey Alexandrovich<br>Group Р32101<br>Variant №1206</h3>
            </td>
        </tr>
    </table>
</header>
<main class="content">
    <div style="width: 100%; display: flex">
        <div class="form" style="width: 60%;">
            <form id="form"  class="validateForm" method="post">
                <div class="inputField">
                    <input type="text" name="x_coordinate" class="x text-field" placeholder="Enter X [-5,3].">
                    <label>Enter X [-5,3].</label>
                </div>
                <div class="inputField">
                    <input type="text" name="y_coordinate" class="y text-field" placeholder="Enter Y [-5,3].">
                    <label>Enter Y [-5,3].</label>
                </div>
                <div class="inputField">
                    <input type="text" name="r_coordinate" class="r text-field" placeholder="Enter R [1,4].">
                    <label>Enter R [1,4].</label>
                </div>
                <div>
                    <input type="submit" class="validate_button submitButton button" value='Submit'/>
                </div>
                <div>
                    <input type="reset" id="reset" class="validate_button resetButton button" value='Reset'/>
                </div>
            </form>
        </div>
        <canvas id="graph" width="300" height="300" >
            Your browser does not support the canvas element.
        </canvas>
    </div>
    <section class="table_section">

        <!-- Таблица регистрирующая попадания -->
        <div>
            <jsp:include page="table.jsp" />
        </div>
    </section>
</main>
<footer class="content">
    <time>
        ITMO University<br>Saint Petersburg<br>2022
    </time>
</footer>
<script src="https://code.jquery.com/jquery-3.5.1.min.js"></script>
<script src="js/main.js" type="module"></script>
<script src="js/graph.js" type="module"></script>
</body>
</html>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<jsp:useBean id="error" class="com.lapin.bean.HttpError" scope="session"/>
<html>
<head>
    <title><%=error.getStatusCode()%> Error</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
<img style="width: 20%" src="img/error1.gif">
<h1><%=error.getStatusCode()%></h1>
<h3><%=error.getErrorMessage()%></h3>
<div id="back">
    <button class="button" id="backbutton">Try again</button>
</div>
<script src="https://code.jquery.com/jquery-3.5.1.min.js"></script>
<script src="js/errorpage.js" type="module"></script>
</body>
</html>

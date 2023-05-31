<%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 16/04/2023
  Time: 5:56 pm
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <title>Homeowner's Association Database Login Page</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
<h1>Homeowner's Association Database Login Page</h1>
<form name = "login" action="login.jsp" method="POST">
    Name: <input type ="text" name ="name" id="name"><br><br>
    Officer ID: <input type="number" name = "hoid" id="hoid" required><br><br>
    <input type="submit" value="Submit" name="login" />
</form>
</body>
</html>

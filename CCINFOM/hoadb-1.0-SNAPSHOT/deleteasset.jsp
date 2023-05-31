<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="java.sql.*, java.util.*, hoadb.*" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Delete Asset Processing</title>
</head>
<body>
<h1>Deleting Wrongly Encoded Asset</h1>
<jsp:useBean id="assetBean" class="com.example.hoadb.Asset" scope="session" />

<%
    try {
        assetBean.failed = false;
        assetBean.asset_id = Integer.parseInt(request.getParameter("asset_id"));
        assetBean.deleteRecord();%>
        Deleted Asset:<br>
        Asset ID: <%=assetBean.asset_id%>
<%} catch (NumberFormatException e) { %>
        No Asset Selected.
<%}%> <br><br>
click <a href="index.jsp">here to go back to Main Menu</a><br>
</body>
</html>

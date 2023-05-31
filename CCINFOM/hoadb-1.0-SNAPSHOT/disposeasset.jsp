<%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 14/04/2023
  Time: 4:54 pm
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import ="java.sql.*, java.util.*, hoadb.*" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <title>Asset Disposal</title>
</head>
<body>
    <h1>Disposal of the selected Asset</h1>
    <jsp:useBean id="assetBean" class="com.example.hoadb.Asset" scope="session" />
    <%
        assetBean.failed = false;
        try {
            assetBean.asset_id = Integer.parseInt(request.getParameter("asset_id"));
            assetBean.disposeAsset();%>
            Disposed Asset:<br>
            Asset ID: <%=assetBean.asset_id%>
            <h4>Record has been successfully updated</h4>
    <%} catch (NumberFormatException e) { %>
            No Asset Selected.
    <%}%> <br><br>


<a href="index.jsp">Main Menu</a>

</body>
</html>

<%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 14/04/2023
  Time: 2:18 pm
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="java.sql.*, java.util.*, hoadb.*" %>
<%@ page import="com.example.hoadb.Asset" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <title>Asset Disposal</title>
</head>
<body>
    <h1>Asset Disposal Form</h1>
    <jsp:useBean id="assetBean" class="com.example.hoadb.Asset" scope="session" />
    <%assetBean.loadAssets(true, "SELECT * FROM view_assets WHERE STATUS NOT LIKE \"X\";");%>

    <form name  = "disposeasset" action="disposeasset.jsp" method = "POST">
        Asset ID: <select name="asset_id" id="asset_id" required>
        <option value = "none">None</option>
        <%
            for (int i =0; i < assetBean.assets.size(); i++){
                Asset a = new Asset();
                a = assetBean.assets.get(i);
                System.out.println(assetBean.assets.get(i));
        %>
        <option value = "<%=a.asset_id%>"> <%=a.asset_id%> - <%=a.asset_name%></option>
        <% } %>
    </select> <br><br>

        <input type="submit" value="Dispose Asset" name="Dispose Asset" />
        <br><br>
        <a href="index.jsp">Back to Main Menu</a>
    </form>
</body>
</html>

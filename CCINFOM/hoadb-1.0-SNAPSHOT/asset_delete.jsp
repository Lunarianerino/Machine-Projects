<%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 14/04/2023
  Time: 2:18 pm
  To change this template use File | Settings | File Templates.
--%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="java.sql.*, java.util.*, hoadb.*" %>
<%@page import="com.example.hoadb.Asset" %>



<html>
    <head>
        <link rel="stylesheet" href="style.css">
        <meta http-equiv="Content-Type" content="text/html"; =UTF=8">
        <title>Asset Update Form</title>
    </head>
    <body>
        <h1>Asset Update Form</h1>
        <jsp:useBean id="assetBean" class="com.example.hoadb.Asset" scope="session"/>
        <%assetBean.loadAssets(true,
                "SELECT * FROM view_assets_condition a LEFT JOIN view_assets_condition b ON a.asset_id = b.enclosing_asset WHERE b.enclosing_asset IS NULL;");%>
        <h6>Only includes assets without rental and activity records.</h6>

        Table of Assets<br>
        <table style="table-layout: fixed; width: 20%">
            <tr>
                <td>ID</td>
                <td>Name</td>
                <td>Description</td>
            </tr>
            <%
                for (int i=0; i < assetBean.assets.size(); i++){
                    Asset a = new Asset();
                    a = assetBean.assets.get(i);
            %>
            <tr>
                <td><%=a.asset_id%></td>
                <td><%=a.asset_name%></td>
                <td style="word-wrap: break-word"><%=a.asset_description%></td>
            </tr>
            <% } %>
        </table><br><br>
        <form name  = "deleteasset" action="deleteasset.jsp" method = "POST">
            Asset ID: <select name="asset_id" id="asset_id" required>
            <option value = "none">None</option>
                <%
                    for (int i =0; i < assetBean.assets.size(); i++){
                        Asset a = new Asset();
                        a = assetBean.assets.get(i);
                %>
            <option value = "<%=a.asset_id%>"> <%=a.asset_id%></option>
            <% } %>
            </select> <br><br>

            <input type="submit" value="Delete Asset" name="deleteasset" />
        </form>
    </body>
</html>

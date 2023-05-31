<%@ page import="com.example.hoadb.Asset" %><%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 14/04/2023
  Time: 2:17 pm
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <meta http-equiv="Content-Type" content="text/html;  =UTF-8">
    <title>Update Asset Form</title>
</head>
<body>
    <h1>Update Asset Form</h1>
    <jsp:useBean id="assetBean" class="com.example.hoadb.Asset" scope="session" />
    <%assetBean.loadAssets(); %>
    <%assetBean.loadHOAName(); %>
    <form name = "assetupdate" action="asset_update2.jsp" method="POST">
        Asset to edit:
        <select name="assetindex" id="assetindex">
            <option value = "none">None</option>
            <%
                System.out.println("Number of Assets: " + assetBean.assets.size());
                for (int i = 0; i < assetBean.assets.size(); i++) {
                    Asset a = new Asset();
                    a = assetBean.assets.get(i);
                    System.out.println(a);%>
            <option value = "<%=i%>"><%=a.asset_id%> - <%=a.asset_name%></option>
            <% }%>
        </select>
        <input type="submit" value="Update Asset" name="Update Asset" />
    </form>

</body>
</html>

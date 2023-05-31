<%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 14/04/2023
  Time: 5:24 pm
  To change this template use File | Settings | File Templates.
--%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="java.sql.*, java.util.*, hoadb.*" %>
<%@ page import="com.example.hoadb.AssetActivity" %>

<html>
<head>
    <link rel="stylesheet" href="style.css">
    <title>Asset Activity Deletion</title>
</head>
<body>
    <h1>Asset Activity Deletion</h1>
    <jsp:useBean id="activityBean" class="com.example.hoadb.AssetActivity" scope="session" />
    <form name = "deleteactivity" action = "deleteactivity.jsp" method = "POST">
        <select name="activityid" id="activityid" required>
            <option value = "none">None</option>
            <%
                activityBean.loadActivities("status NOT LIKE \"D\"");
                System.out.println(activityBean.assetActivities.size());
                for (int i = 0; i < activityBean.assetActivities.size(); i++) {
                    AssetActivity a = new AssetActivity();
                    a = activityBean.assetActivities.get(i);
                    System.out.println(a.asset_id);
            %>
            <option value = "<%=a.asset_id%>-<%=a.activity_date%>"> <%=a.asset_id%> - <%=a.getAssetName()%> (<%=a.activity_date%>)</option>
            <%}%>
        </select><br><br>
        <input type="submit" value="Delete Activity" name="completeactivity" />
    </form>
</body>
</html>

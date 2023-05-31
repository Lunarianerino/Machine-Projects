<%@ page import="com.example.hoadb.AssetActivity" %><%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 14/04/2023
  Time: 5:23 pm
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <title>Complete an Activity</title>
</head>
<body>
    <h1>Complete an Activity</h1>
    <jsp:useBean id="activityBean" class="com.example.hoadb.AssetActivity" scope="session" />

    <form name = "completeactivity" action = "completeactivity.jsp" method = "POST">
        <select name="activityid" id="activityid">
        <option value = "none">None</option>
        <%
            activityBean.loadActivities("status NOT LIKE \"C\"");
            System.out.println(activityBean.assetActivities.size());
                for (int i = 0; i < activityBean.assetActivities.size(); i++) {
                    AssetActivity a = new AssetActivity();
                    a = activityBean.assetActivities.get(i);
                    System.out.println(a.asset_id);
        %>
            <option value = "<%=a.asset_id%>-<%=a.activity_date%>"> <%=a.asset_id%> - <%=a.getAssetName()%> (<%=a.activity_date%>)</option>

            <%}%>
        </select><br><br>

        <input type="submit" value="Complete Activity" name="completeactivity" />
    </form>
</body>
</html>

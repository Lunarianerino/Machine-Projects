<%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 14/04/2023
  Time: 11:59 pm
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <title>Completed Activity</title>
</head>
<body>
    <h1>Completed Activity</h1>
    <jsp:useBean id="activityBean" class="com.example.hoadb.AssetActivity" scope="session" />
    <%
        String activityid = request.getParameter("activityid");
        System.out.println(activityid);

        if (!activityid.equals("none"))
        {
            String[] activity_pk = activityid.split("-",2);
            System.out.println(activity_pk[0]);
            System.out.println(activity_pk[1]);
            int asset_id = Integer.parseInt(activity_pk[0]);
            activityBean.updateActivity("SET status = \"C\" WHERE asset_id = " + asset_id + " AND activity_date = \"" + activity_pk[1] + "\"");%>
            Completed Activity Successfully.
        <%} else {
        %>
            No activity was selected.
        <% ;}%>
    <br><br>Click <a href="index.jsp">here to go back to main menu</a><br>

</body>
</html>

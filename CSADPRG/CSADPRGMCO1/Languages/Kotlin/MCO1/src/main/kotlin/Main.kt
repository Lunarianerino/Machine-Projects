fun computeSSS(monthlySalary : Float) : Float
{
    var regularFee : Float = when
    {
        monthlySalary <= 3250f -> 135.00f
        monthlySalary <= 3750f -> 157.50f
        monthlySalary <= 4250f -> 180.00f
        monthlySalary <= 4750f -> 202.50f
        monthlySalary <= 5250f -> 225.00f
        monthlySalary <= 5750f -> 247.50f
        monthlySalary <= 6250f -> 270.00f
        monthlySalary <= 6750f -> 292.50f
        monthlySalary <= 7250f -> 315.00f
        monthlySalary <= 7750f -> 337.50f
        monthlySalary <= 8250f -> 360.00f
        monthlySalary <= 8750f -> 382.50f
        monthlySalary <= 9250f -> 405.00f
        monthlySalary <= 9750f -> 427.50f
        monthlySalary <= 10250f -> 450.00f
        monthlySalary <= 10750f -> 472.50f
        monthlySalary <= 11250f -> 495.00f
        monthlySalary <= 11750f -> 517.50f
        monthlySalary <= 12250f -> 540.00f
        monthlySalary <= 12750f -> 562.50f
        monthlySalary <= 13250f -> 585.00f
        monthlySalary <= 13750f -> 607.50f
        monthlySalary <= 14250f -> 630.00f
        monthlySalary <= 14750f -> 652.50f
        monthlySalary <= 15250f -> 675.00f
        monthlySalary <= 15750f -> 697.50f
        monthlySalary <= 16250f -> 720.00f
        monthlySalary <= 16750f -> 742.50f
        monthlySalary <= 17250f -> 765.00f
        monthlySalary <= 17750f -> 787.50f
        monthlySalary <= 18250f -> 810.00f
        monthlySalary <= 18750f -> 832.50f
        monthlySalary <= 19250f -> 855.00f
        monthlySalary <= 19750f -> 877.50f
        else -> 900.00f
    }

    var providentFund : Float = when
    {
        monthlySalary >= 20250f -> when
        {
            monthlySalary <= 20750f -> 22.50f
            monthlySalary <= 21250f -> 45.00f
            monthlySalary <= 21750f -> 67.50f
            monthlySalary <= 22250f -> 90.00f
            monthlySalary <= 22750f -> 112.50f
            monthlySalary <= 23250f -> 135.00f
            monthlySalary <= 23750f -> 157.50f
            monthlySalary <= 24250f -> 180.00f
            monthlySalary <= 24750f -> 202.50f
            else -> 225.00f
        }
        else -> 0.00f
    }

    return regularFee + providentFund
}

fun computePhilHealth(monthlySalary : Float) : Float
{
    return when
    {
        monthlySalary <= 10000f -> 350.00f / 2
        monthlySalary > 1000f && monthlySalary < 60000f -> monthlySalary * 0.035f / 2f
        else -> 2450.00f / 2
    }
}

fun computePagibig(monthlySalary : Float) : Float
{
    return when
    {
        monthlySalary <= 1500f -> monthlySalary * 0.01f
        monthlySalary <= 5000f -> monthlySalary * 0.02f
        else -> 100.00f
    }
}

fun computeIncomeTax(taxableIncome : Float)  : Float
{
    return when
    {
        taxableIncome < 20833f -> 0.00f
        taxableIncome < 33333f -> (taxableIncome - 20833f) * 0.2f
        taxableIncome < 66667f -> 2500.00f + (taxableIncome - 33333) * 0.25f
        taxableIncome < 166667f -> 10833.33f + (taxableIncome - 66667f) * 0.2f
        taxableIncome < 666667f -> 40833.33f + (taxableIncome - 166667f) * 0.2f
        else -> 200833.33f + (taxableIncome - 666667f) * 0.2f
    }
}


fun main(args: Array<String>) {
    println("========================NET SALARY CALCULATOR========================")
    println("Please enter your monthly salary:")

    var monthlySalary : Float = readln().toFloat()

    var sssFee : Float = computeSSS(monthlySalary)
    var philHealthFee : Float = computePhilHealth(monthlySalary)
    var pagibigFee : Float = computePagibig(monthlySalary)

    var totalContributions : Float = sssFee + philHealthFee + pagibigFee

    var taxableIncome : Float = monthlySalary - totalContributions

    var incomeTax : Float = computeIncomeTax(taxableIncome)

    var totalDeductions : Float = incomeTax + totalContributions
    var netMonthlyPay : Float = monthlySalary - totalDeductions

    println("==============================BREAKDOWN==============================")
    println("| Monthly Salary = ₱%.2f".format(monthlySalary))
    println("========================MONTHLY CONTRIBUTIONS========================")
    println("| SSS = ₱%.2f".format(sssFee))
    println("| PhilHealth = ₱%.2f".format(philHealthFee))
    println("| Pag-Ibig = ₱%.2f".format(pagibigFee))
    println("| +_________________________")
    println("| Total Contributions = ₱%.2f".format(totalContributions))
    println("================================TAXES================================")
    println("| Taxable Income = ₱%.2f".format(taxableIncome))
    println("| Income Tax = ₱%.2f".format(incomeTax))
    println("=============================NET SALARY==============================")
    println("| Total Deductions = ₱%.2f".format(totalDeductions))
    println("| Net Monthly Pay = ₱%.2f".format(netMonthlyPay))
}
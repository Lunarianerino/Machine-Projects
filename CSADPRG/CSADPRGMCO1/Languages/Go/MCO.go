package main

import (
	"fmt"
	"math"
	"os"
)

type taxBracket struct {
	nMin       float32
	nMax       float32
	nTax       float32
	percentage float32
}

func calculateMonthlyIncomeTax(nMonthlyIncome float32, result chan<- float32) {

	var taxBrackets = []taxBracket{
		{0, 20833, 0, 0},
		{20833, 33332, 0, 0.20},
		{33332, 66666, 2500, 0.25},
		{66666, 166666, 10833.33, 0.30},
		{166666, 666666, 40833.33, 0.32},
		//to infinity
		{666666, float32(math.Inf(1)), 200833.33, 0.35},
	}

	var nTax float32
	for _, taxBracket := range taxBrackets {
		//finds the first bracket that the monthly income is within
		if nMonthlyIncome >= taxBracket.nMin && nMonthlyIncome <= taxBracket.nMax {
			//return the tax amount for that bracket
			nTax = taxBracket.nTax + (nMonthlyIncome-taxBracket.nMin)*taxBracket.percentage
			result <- nTax
		}
	}
	result <- nTax

}
func calculateMonthlySSSTax(nMonthlyIncome float32, result chan<- float32) {
	//uses a switch case for all ranges of the SSS tax brackets and returns the tax amount
	var x float32
	switch {
	case nMonthlyIncome <= 3250.00 && nMonthlyIncome >= 1000:
		x = 135
	case nMonthlyIncome <= 3750.00 && nMonthlyIncome > 3250.00:
		x = 157.50
	case nMonthlyIncome <= 4250.00 && nMonthlyIncome > 3750.00:
		x = 180
	case nMonthlyIncome <= 4750.00 && nMonthlyIncome > 4250.00:
		x = 202.50
	case nMonthlyIncome <= 5250.00 && nMonthlyIncome > 4750.00:
		x = 225
	case nMonthlyIncome <= 5750.00 && nMonthlyIncome > 5250.00:
		x = 247.50
	case nMonthlyIncome <= 6250.00 && nMonthlyIncome > 5750.00:
		x = 270
	case nMonthlyIncome <= 6750.00 && nMonthlyIncome > 6250.00:
		x = 292.50
	case nMonthlyIncome <= 7250.00 && nMonthlyIncome > 6750.00:
		x = 315
	case nMonthlyIncome <= 7750.00 && nMonthlyIncome > 7250.00:
		x = 337.50
	case nMonthlyIncome <= 8250.00 && nMonthlyIncome > 7750.00:
		x = 360
	case nMonthlyIncome <= 8750.00 && nMonthlyIncome > 8250.00:
		x = 382.50
	case nMonthlyIncome <= 9250.00 && nMonthlyIncome > 8750.00:
		x = 405
	case nMonthlyIncome <= 9750.00 && nMonthlyIncome > 9250.00:
		x = 427.50
	case nMonthlyIncome <= 10250.00 && nMonthlyIncome > 9750.00:
		x = 450
	case nMonthlyIncome <= 10750.00 && nMonthlyIncome > 10250.00:
		x = 472.50
	case nMonthlyIncome <= 11250.00 && nMonthlyIncome > 10750.00:
		x = 495
	case nMonthlyIncome <= 11750.00 && nMonthlyIncome > 11250.00:
		x = 517.50
	case nMonthlyIncome <= 12250.00 && nMonthlyIncome > 11750.00:
		x = 540
	case nMonthlyIncome <= 12750.00 && nMonthlyIncome > 12250.00:
		x = 562.50
	case nMonthlyIncome <= 13250.00 && nMonthlyIncome > 12750.00:
		x = 585
	case nMonthlyIncome <= 13750.00 && nMonthlyIncome > 13250.00:
		x = 607.50
	case nMonthlyIncome <= 14250.00 && nMonthlyIncome > 13750.00:
		x = 630
	case nMonthlyIncome <= 14750.00 && nMonthlyIncome > 14250.00:
		x = 652.50
	case nMonthlyIncome <= 15250.00 && nMonthlyIncome > 14750.00:
		x = 675
	case nMonthlyIncome <= 15750.00 && nMonthlyIncome > 15250.00:
		x = 697.50
	case nMonthlyIncome <= 16250.00 && nMonthlyIncome > 15750.00:
		x = 720
	case nMonthlyIncome <= 16750.00 && nMonthlyIncome > 16250.00:
		x = 742.50
	case nMonthlyIncome <= 17250.00 && nMonthlyIncome > 16750.00:
		x = 765
	case nMonthlyIncome <= 17750.00 && nMonthlyIncome > 17250.00:
		x = 787.50
	case nMonthlyIncome <= 18250.00 && nMonthlyIncome > 17750.00:
		x = 810
	case nMonthlyIncome <= 18750.00 && nMonthlyIncome > 18250.00:
		x = 832.50
	case nMonthlyIncome <= 19250.00 && nMonthlyIncome > 18750.00:
		x = 855
	case nMonthlyIncome <= 19750.00 && nMonthlyIncome > 19250.00:
		x = 877.50
	case nMonthlyIncome <= 20250.00 && nMonthlyIncome > 19750.00:
		x = 900
	case nMonthlyIncome <= 20750.00 && nMonthlyIncome > 20250.00:
		x = 922.50
	case nMonthlyIncome <= 21250.00 && nMonthlyIncome > 20750.00:
		x = 945
	case nMonthlyIncome <= 21750.00 && nMonthlyIncome > 21250.00:
		x = 967.50
	case nMonthlyIncome <= 22250.00 && nMonthlyIncome > 21750.00:
		x = 990
	case nMonthlyIncome <= 22750.00 && nMonthlyIncome > 22250.00:
		x = 1012.50
	case nMonthlyIncome <= 23250.00 && nMonthlyIncome > 22750.00:
		x = 1035
	case nMonthlyIncome <= 23250.00 && nMonthlyIncome > 23250.00:
		x = 1057.50
	case nMonthlyIncome <= 24250.00 && nMonthlyIncome > 23750.00:
		x = 1080
	case nMonthlyIncome <= 24750.00 && nMonthlyIncome > 24250.00:
		x = 1102.50
	case nMonthlyIncome > 24750.00:
		x = 1125
	default:
		x = 0
	}
	result <- x
}

func calculateMonthlyPhilHealth(nMonthlyIncome float32, result chan<- float32) {
	//2022 rates
	switch {
	case nMonthlyIncome <= 10000:
		result <- 350 / 2
	case nMonthlyIncome > 10000 && nMonthlyIncome < 70000:
		result <- (nMonthlyIncome * 0.035) / 2
	case nMonthlyIncome >= 70000:
		result <- 2450 / 2
	}
}

func calculateMonthlyPagIbig(nMonthlyIncome float32, result chan<- float32) {
	if nMonthlyIncome <= 1500 {
		result <- nMonthlyIncome * 0.01
	} else if nMonthlyIncome > 1500 && nMonthlyIncome <= 5000 {
		result <- nMonthlyIncome * 0.02
	} else if nMonthlyIncome > 5000 {
		result <- 5000 * 0.02
	}
}

func calculate(nMonthlyIncome float32) {
	//call methods to calculate monthly deductions
	var incomeTax = make(chan float32)
	var sss = make(chan float32)
	var philHealth = make(chan float32)
	var pagIbig = make(chan float32)

	//call the goroutines to calculate the deductions
	go calculateMonthlySSSTax(nMonthlyIncome, sss)
	go calculateMonthlyPhilHealth(nMonthlyIncome, philHealth)
	go calculateMonthlyPagIbig(nMonthlyIncome, pagIbig)

	//receive the results
	nMonthlySSS := <-sss
	nMonthlyPhilHealth := <-philHealth
	nMonthlyPagIbig := <-pagIbig
	go calculateMonthlyIncomeTax(nMonthlyIncome-nMonthlySSS-nMonthlyPhilHealth-nMonthlyPagIbig, incomeTax)
	nMonthlyTax := <-incomeTax

	//output the results
	fmt.Println("============================== BREAKDOWN IN PHILIPPINE PESOS ==============================")
	fmt.Printf("Monthly Salary = P%.2f\n", nMonthlyIncome)
	fmt.Println("============================== MONTHLY CONTRIBUTIONS ======================================")
	fmt.Printf("Monthly SSS = P%.2f\nMonthly PhilHealth = P%.2f\nMonthly PagIbig = P%.2f\n", nMonthlySSS, nMonthlyPhilHealth, nMonthlyPagIbig)
	fmt.Println("+____________________________")
	fmt.Printf("Total Contributions: P%.2f\n", nMonthlySSS+nMonthlyPhilHealth+nMonthlyPagIbig)
	fmt.Println("============================== TAXES ======================================================")
	fmt.Printf("Taxable Income = P%.2f\n", nMonthlyIncome-(nMonthlySSS+nMonthlyPhilHealth+nMonthlyPagIbig))
	fmt.Printf("Income Tax = P%.2f\n", nMonthlyTax)
	fmt.Println("============================== NET SALARY =================================================")
	fmt.Printf("Total Deductions = P%.2f\n", nMonthlyTax+nMonthlySSS+nMonthlyPhilHealth+nMonthlyPagIbig)
	fmt.Printf("Net Monthly Salary = P%.2f\n", nMonthlyIncome-(nMonthlyTax+nMonthlySSS+nMonthlyPhilHealth+nMonthlyPagIbig))
}

func main() {

	for {
		fmt.Println("======================== NET TAX CALCULATOR ========================")
		fmt.Println("Main Menu")
		fmt.Println("1. Calculate Tax")
		fmt.Println("2. Exit")
		fmt.Printf("Enter choice: ")
		var nChoice int
		fmt.Scanln(&nChoice)
		switch nChoice {
		case 1:
			fmt.Printf("Enter Monthly Income in PHP: ")
			var nMonthlyIncome float32
			fmt.Scanln(&nMonthlyIncome)

			//rejects negative values and 0
			if nMonthlyIncome <= 0 {
				fmt.Println("Invalid input")
				break
			}

			calculate(nMonthlyIncome)
		case 2:
			os.Exit(0)
		default:
			fmt.Println("Invalid choice")
		}
	}

}

// to run: go run ./Languages/Go/MCO.go

package main

import "fmt"

// declare an interface employee
type Employee interface {
	GetName() string
}

// create a struct
type Engineer struct {
	Name string
}

type Finance struct {
	Name string
}

// create a method that implements the Employees's interface
func (e *Engineer) GetName() string {
	return "employee name:" + e.Name

}

// create a method that implements the Employee's interface
func (f Finance) GetName() string {
	return "employee name:" + f.Name
}

// print out the engineer's details
func EmployeeDetails(e Employee) {
	fmt.Println(e.GetName())
}

func main() {
	engineer := &Engineer{
		Name: "Rebeccah",
	}
	EmployeeDetails(engineer)

	finance := &Finance{
		Name: "John Doe",
	}
	EmployeeDetails(finance)
}

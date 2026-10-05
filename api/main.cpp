#include "crow.h"

#include "../backend/StudentManager.h"

#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <iomanip>
#include <algorithm>
#include <map>
#include <cstdlib>

using namespace std;


// =========================
// READ FILE
// =========================

string readFile(const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return "File could not be opened.";
    }

    stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}


// =========================
// REPLACE HTML PLACEHOLDER
// =========================

string replacePlaceholder(
    string html,
    const string& placeholder,
    const string& value
)
{
    size_t position = html.find(placeholder);

    while (position != string::npos)
    {
        html.replace(
            position,
            placeholder.length(),
            value
        );

        position = html.find(
            placeholder,
            position + value.length()
        );
    }

    return html;
}


// =========================
// URL DECODE
// =========================

string urlDecode(const string& value)
{
    string result;

    for (size_t i = 0; i < value.length(); i++)
    {
        if (value[i] == '+')
        {
            result += ' ';
        }
        else if (
            value[i] == '%' &&
            i + 2 < value.length()
        )
        {
            string hex =
                value.substr(i + 1, 2);

            char decoded =
                static_cast<char>(
                    strtol(
                        hex.c_str(),
                        nullptr,
                        16
                    )
                );

            result += decoded;

            i += 2;
        }
        else
        {
            result += value[i];
        }
    }

    return result;
}


// =========================
// PARSE FORM DATA
// =========================

map<string, string> parseFormData(
    const string& body
)
{
    map<string, string> data;

    stringstream ss(body);

    string pair;

    while (getline(ss, pair, '&'))
    {
        size_t equalPosition =
            pair.find('=');

        if (equalPosition == string::npos)
        {
            continue;
        }

        string key =
            pair.substr(
                0,
                equalPosition
            );

        string value =
            pair.substr(
                equalPosition + 1
            );

        data[urlDecode(key)] =
            urlDecode(value);
    }

    return data;
}


// =========================
// MAIN
// =========================

int main()
{
    crow::SimpleApp app;

    StudentManager manager;

    // Load students from students.dat
    manager.loadFromFile();
    bool loggedIn = false;
    // =========================
// LOGIN PAGE
// =========================

CROW_ROUTE(app, "/login")([&]()
{
    return crow::response(
        "text/html",
        readFile("pages/login.html")
    );
});
// =========================
// LOGIN PROCESS
// =========================

CROW_ROUTE(app, "/login")
.methods(crow::HTTPMethod::POST)
([&](const crow::request& req)
{
    map<string, string> formData =
        parseFormData(req.body);

    if (
        formData.find("username") == formData.end() ||
        formData.find("password") == formData.end()
    )
    {
        return crow::response(
            "<html>"
            "<body>"
            "<h2>Invalid login data.</h2>"
            "<a href='/login'>Go Back</a>"
            "</body>"
            "</html>"
        );
    }

    string username =
        formData["username"];

    string password =
        formData["password"];

if (username == "milan_admin" &&
    password == "Milangudu@123#")
{
   
}
    {
        loggedIn = true;

        crow::response response;

        response.code = 302;

        response.set_header(
            "Location",
            "/"
        );

        return response;
    }

    return crow::response(
        "<html>"
        "<head>"
        "<title>Login Failed</title>"
        "</head>"
        "<body>"
        "<h2>Invalid username or password.</h2>"
        "<a href='/login'>Try Again</a>"
        "</body>"
        "</html>"
    );
});
// =========================
// LOGOUT
// =========================

CROW_ROUTE(app, "/logout")([&]()
{
    loggedIn = false;

    crow::response response;

    response.code = 302;

    response.set_header(
        "Location",
        "/login"
    );

    return response;
});


    // =========================
    // DYNAMIC DASHBOARD
    // =========================

    CROW_ROUTE(app, "/")([&]()
{
    if (!loggedIn)
    {
        crow::response response;

        response.code = 302;

        response.set_header(
            "Location",
            "/login"
        );

        return response;
    }

    string html =
        readFile("pages/dashboard.html");

        // Get all students
        vector<Student> students =
            manager.getStudents();


        // Sort students by ID
        // 101, 102, 103, 104...
        sort(
            students.begin(),
            students.end(),
            [](const Student& a, const Student& b)
            {
                return a.getId() < b.getId();
            }
        );


        // -------------------------
        // Total Students
        // -------------------------

        int totalStudents =
            students.size();


        // -------------------------
        // Total Courses
        // -------------------------

        set<string> courses;

        for (const Student& student : students)
        {
            courses.insert(
                student.getCourse()
            );
        }

        int totalCourses =
            courses.size();


        // -------------------------
        // Average Marks
        // -------------------------

        float averageMarks = 0;

        if (!students.empty())
        {
            float totalMarks = 0;

            for (const Student& student : students)
            {
                totalMarks +=
                    student.getMarks();
            }

            averageMarks =
                totalMarks / students.size();
        }


        // -------------------------
        // Top Marks
        // -------------------------

        float topMarks = 0;

        for (const Student& student : students)
        {
            topMarks =
                max(
                    topMarks,
                    student.getMarks()
                );
        }


        // -------------------------
        // Recent Students
        // -------------------------

        stringstream recentStudents;

        if (students.empty())
        {
            recentStudents
                << "<tr>"
                << "<td colspan='5' class='empty'>"
                << "No students available"
                << "</td>"
                << "</tr>";
        }
        else
        {
        

            // Show first 5 students
            // in ascending ID order
            for (
                auto it = students.begin();
                it != students.end(); 
              
               
                ++it
            )
            {
                const Student& student = *it;

                recentStudents
                    << "<tr>";

                recentStudents
                    << "<td>"
                    << student.getId()
                    << "</td>";

                recentStudents
                    << "<td>"
                    << student.getName()
                    << "</td>";

                recentStudents
                    << "<td>"
                    << student.getAge()
                    << "</td>";

                recentStudents
                    << "<td>"
                    << student.getCourse()
                    << "</td>";

                recentStudents
                    << "<td>"
                    << fixed
                    << setprecision(2)
                    << student.getMarks()
                    << "</td>";

                recentStudents
                    << "</tr>";
               
            }
        }


        // -------------------------
        // Replace HTML placeholders
        // -------------------------

        html = replacePlaceholder(
            html,
            "{{TOTAL_STUDENTS}}",
            to_string(totalStudents)
        );


        html = replacePlaceholder(
            html,
            "{{TOTAL_COURSES}}",
            to_string(totalCourses)
        );


        stringstream avg;

        avg << fixed
            << setprecision(2)
            << averageMarks;

        html = replacePlaceholder(
            html,
            "{{AVERAGE_MARKS}}",
            avg.str()
        );


        stringstream top;

        top << fixed
            << setprecision(2)
            << topMarks;

        html = replacePlaceholder(
            html,
            "{{TOP_MARKS}}",
            top.str()
        );


        html = replacePlaceholder(
            html,
            "{{RECENT_STUDENTS}}",
            recentStudents.str()
        );


        return crow::response(
            "text/html",
            html
        );
    });


    // =========================
    // ADD STUDENT PAGE
    // =========================

    CROW_ROUTE(app, "/add")([&]()
    {
        return crow::response(
            "text/html",
            readFile("pages/add.html")
        );
    });


    // =========================
    // ADD STUDENT FORM
    // =========================

    CROW_ROUTE(app, "/add")
    .methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        map<string, string> formData =
            parseFormData(req.body);

        if (
            formData.find("id") == formData.end() ||
            formData.find("name") == formData.end() ||
            formData.find("age") == formData.end() ||
            formData.find("course") == formData.end() ||
            formData.find("marks") == formData.end()
        )
        {
            return crow::response(
                "<html>"
                "<body>"
                "<h2>Invalid form data.</h2>"
                "<a href='/add'>Go Back</a>"
                "</body>"
                "</html>"
            );
        }

        try
        {
            int id =
                stoi(formData["id"]);

            string name =
                formData["name"];

            int age =
                stoi(formData["age"]);

            string course =
                formData["course"];

            float marks =
                stof(formData["marks"]);


            bool success =
                manager.addStudent(
                    id,
                    name,
                    age,
                    course,
                    marks
                );


            if (success)
            {
                return crow::response(
                    "<html>"
                    "<head>"
                    "<meta charset='UTF-8'>"
                    "<title>Success</title>"
                    "</head>"
                    "<body>"
                    "<h2>Student added successfully!</h2>"
                    "<p>The student has been saved to students.dat.</p>"
                    "<a href='/'>Go to Dashboard</a>"
                    "</body>"
                    "</html>"
                );
            }


            return crow::response(
                "<html>"
                "<head>"
                "<meta charset='UTF-8'>"
                "<title>Add Student</title>"
                "</head>"
                "<body>"
                "<h2>Failed to add student.</h2>"
                "<p>Student ID may already exist or the input is invalid.</p>"
                "<a href='/add'>Go Back</a>"
                "</body>"
                "</html>"
            );
        }
        catch (...)
        {
            return crow::response(
                "<html>"
                "<head>"
                "<meta charset='UTF-8'>"
                "<title>Error</title>"
                "</head>"
                "<body>"
                "<h2>Invalid input.</h2>"
                "<p>Please enter valid values.</p>"
                "<a href='/add'>Go Back</a>"
                "</body>"
                "</html>"
            );
        }
    });


   
// =========================
// VIEW ALL STUDENTS
// =========================

CROW_ROUTE(app, "/students")([&]()
{
    string html =
        readFile("pages/students.html");

    vector<Student> students =
        manager.getStudents();

    // Sort by Student ID
    sort(
        students.begin(),
        students.end(),
        [](const Student& a, const Student& b)
        {
            return a.getId() < b.getId();
        }
    );

    stringstream rows;

    if (students.empty())
    {
        rows
            << "<tr>"
            << "<td colspan='5' class='empty'>"
            << "No students available"
            << "</td>"
            << "</tr>";
    }
    else
    {
        for (const Student& student : students)
        {
            rows << "<tr>";

            rows
                << "<td>"
                << student.getId()
                << "</td>";

            rows
                << "<td>"
                << student.getName()
                << "</td>";

            rows
                << "<td>"
                << student.getAge()
                << "</td>";

            rows
                << "<td>"
                << student.getCourse()
                << "</td>";

            rows
                << "<td>"
                << fixed
                << setprecision(2)
                << student.getMarks()
                << "</td>";

            rows << "</tr>";
        }
    }

    html = replacePlaceholder(
        html,
        "{{STUDENT_ROWS}}",
        rows.str()
    );

    return crow::response(
        "text/html",
        html
    );
});
// =========================
// SEARCH STUDENT PAGE
// =========================

CROW_ROUTE(app, "/search")([&]()
{
    return crow::response(
        "text/html",
        readFile("pages/search.html")
    );
});


// =========================
// SEARCH STUDENT
// =========================

CROW_ROUTE(app, "/search")
.methods(crow::HTTPMethod::POST)
([&](const crow::request& req)
{
    map<string, string> formData =
        parseFormData(req.body);

    if (formData.find("id") == formData.end())
    {
        return crow::response(
            "<html>"
            "<body>"
            "<h2>Invalid Student ID.</h2>"
            "<a href='/search'>Go Back</a>"
            "</body>"
            "</html>"
        );
    }

    try
    {
        int id = stoi(formData["id"]);

        Student* student =
            manager.findStudent(id);

        if (student == nullptr)
        {
            return crow::response(
                "<html>"
                "<head>"
                "<title>Student Not Found</title>"
                "</head>"
                "<body>"
                "<h2>Student not found.</h2>"
                "<p>No student exists with ID: "
                + to_string(id)
                + "</p>"
                "<a href='/search'>Search Again</a>"
                "</body>"
                "</html>"
            );
        }

        stringstream html;

        html << "<html>";
        html << "<head>";
        html << "<title>Student Found</title>";
        html << "</head>";

        html << "<body>";

        html << "<h2>Student Found</h2>";

        html << "<p>ID: "
             << student->getId()
             << "</p>";

        html << "<p>Name: "
             << student->getName()
             << "</p>";

        html << "<p>Age: "
             << student->getAge()
             << "</p>";

        html << "<p>Course: "
             << student->getCourse()
             << "</p>";

        html << "<p>Marks: "
             << student->getMarks()
             << "</p>";

        html << "<br>";

        html << "<a href='/search'>Search Another</a>";

        html << "</body>";
        html << "</html>";

        return crow::response(
            "text/html",
            html.str()
        );
    }
    catch (...)
    {
        return crow::response(
            "<html>"
            "<body>"
            "<h2>Invalid Student ID.</h2>"
            "<a href='/search'>Go Back</a>"
            "</body>"
            "</html>"
        );
    }
});

// =========================
// UPDATE STUDENT PAGE
// =========================

CROW_ROUTE(app, "/update")([&]()
{
    return crow::response(
        "text/html",
        readFile("pages/update.html")
    );
});


// =========================
// UPDATE STUDENT
// =========================

CROW_ROUTE(app, "/update")
.methods(crow::HTTPMethod::POST)
([&](const crow::request& req)
{
    map<string, string> formData =
        parseFormData(req.body);

    if (
        formData.find("id") == formData.end() ||
        formData.find("name") == formData.end() ||
        formData.find("age") == formData.end() ||
        formData.find("course") == formData.end() ||
        formData.find("marks") == formData.end()
    )
    {
        return crow::response(
            "<html>"
            "<body>"
            "<h2>Invalid form data.</h2>"
            "<a href='/update'>Go Back</a>"
            "</body>"
            "</html>"
        );
    }

    try
    {
        int id = stoi(formData["id"]);
        string name = formData["name"];
        int age = stoi(formData["age"]);
        string course = formData["course"];
        float marks = stof(formData["marks"]);

        bool success =
            manager.updateStudent(
                id,
                name,
                age,
                course,
                marks
            );

        if (success)
        {
            return crow::response(
                "<html>"
                "<head>"
                "<title>Update Successful</title>"
                "</head>"
                "<body>"
                "<h2>Student updated successfully!</h2>"
                "<p>Student ID: "
                + to_string(id)
                + "</p>"
                "<a href='/students'>View All Students</a>"
                "<br><br>"
                "<a href='/update'>Update Another Student</a>"
                "</body>"
                "</html>"
            );
        }

        return crow::response(
            "<html>"
            "<body>"
            "<h2>Student not found.</h2>"
            "<p>No student exists with this ID.</p>"
            "<a href='/update'>Go Back</a>"
            "</body>"
            "</html>"
        );
    }
    catch (...)
    {
        return crow::response(
            "<html>"
            "<body>"
            "<h2>Invalid input.</h2>"
            "<a href='/update'>Go Back</a>"
            "</body>"
            "</html>"
        );
    }
});
// =========================
// DELETE STUDENT PAGE
// =========================

CROW_ROUTE(app, "/delete")([&]()
{
    return crow::response(
        "text/html",
        readFile("pages/delete.html")
    );
});


// =========================
// DELETE STUDENT
// =========================

CROW_ROUTE(app, "/delete")
.methods(crow::HTTPMethod::POST)
([&](const crow::request& req)
{
    map<string, string> formData =
        parseFormData(req.body);

    if (formData.find("id") == formData.end())
    {
        return crow::response(
            "<html>"
            "<body>"
            "<h2>Invalid Student ID.</h2>"
            "<a href='/delete'>Go Back</a>"
            "</body>"
            "</html>"
        );
    }

    try
    {
        int id = stoi(formData["id"]);

        bool success =
            manager.deleteStudent(id);

        if (success)
        {
            return crow::response(
                "<html>"
                "<head>"
                "<title>Delete Successful</title>"
                "</head>"
                "<body>"
                "<h2>Student deleted successfully!</h2>"
                "<p>Student ID: "
                + to_string(id)
                + "</p>"
                "<a href='/students'>View All Students</a>"
                "<br><br>"
                "<a href='/delete'>Delete Another Student</a>"
                "</body>"
                "</html>"
            );
        }

        return crow::response(
            "<html>"
            "<body>"
            "<h2>Student not found.</h2>"
            "<p>No student exists with this ID.</p>"
            "<a href='/delete'>Go Back</a>"
            "</body>"
            "</html>"
        );
    }
    catch (...)
    {
        return crow::response(
            "<html>"
            "<body>"
            "<h2>Invalid Student ID.</h2>"
            "<a href='/delete'>Go Back</a>"
            "</body>"
            "</html>"
        );
    }
});
    // =========================
    // CSS
    // =========================

    CROW_ROUTE(
        app,
        "/styles/<string>"
    )
    (
        [](const crow::request&,
           crow::response& res,
           string filename)
        {
            string content =
                readFile(
                    "styles/" + filename
                );


            res.set_header(
                "Content-Type",
                "text/css"
            );


            res.write(content);

            res.end();
        }
    );


    // =========================
    // START SERVER
    // =========================

    app.port(8080)
       .multithreaded()
       .run();
}
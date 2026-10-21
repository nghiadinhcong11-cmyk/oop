#include "../exceptions/Exceptions.h"
#include "../models/ChamCong.h"
#include "../models/Luong.h"
#include "../models/NhanVienFullTime.h"
#include "../models/NhanVienPartTime.h"
#include "../models/NhanVienThucTap.h"
#include "../models/PhongBan.h"
#include "../services/QuanLyChamCong.h"
#include "../services/QuanLyLuong.h"
#include "../services/QuanLyNhanVien.h"
#include "../services/QuanLyPhongBan.h"

#include <cmath>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace fs = filesystem;

class TestFailure : public runtime_error {
public:
    explicit TestFailure(const string& message) : runtime_error(message) {}
};

static void check(bool condition, const string& message) {
    if (!condition) throw TestFailure(message);
}

static bool near(double actual, double expected, double tolerance = 0.01) {
    return fabs(actual - expected) <= tolerance;
}

template <typename ExceptionType, typename Function>
static void expectThrows(Function function, const string& context) {
    try {
        function();
    } catch (const ExceptionType&) {
        return;
    } catch (const exception& error) {
        throw TestFailure(context + ": sai loai ngoai le: " + error.what());
    }
    throw TestFailure(context + ": khong nem ngoai le mong doi");
}

static unique_ptr<NhanVienFullTime> makeFullTime(
    const string& code = "NVFT01", double salary = 10000000, double allowance = 100000) {
    return make_unique<NhanVienFullTime>(
        code, "An", "01/01/2000", "Nam", "0900000001", "an@example.com",
        "Ha Noi", "PB01", "Nhan vien", "01/01/2024", salary, allowance, 0);
}

static unique_ptr<NhanVienPartTime> makePartTime(
    const string& code = "NVPT01", double hourlyRate = 50000) {
    return make_unique<NhanVienPartTime>(
        code, "Binh", "02/02/2001", "Nu", "0900000002", "binh@example.com",
        "Ha Noi", "PB01", "Nhan vien", "02/02/2024", 1, hourlyRate);
}

static unique_ptr<NhanVienThucTap> makeIntern(
    const string& code = "NVT01", double allowanceRate = 25000) {
    return make_unique<NhanVienThucTap>(
        code, "Chi", "03/03/2002", "Nu", "0900000003", "chi@example.com",
        "Ha Noi", "PB01", "Thuc tap", "03/03/2024", 1, allowanceRate);
}

static void writeText(const fs::path& path, const string& text) {
    ofstream file(path);
    check(file.is_open(), "khong tao duoc file thu " + path.string());
    file << text;
    check(static_cast<bool>(file), "khong ghi duoc file thu " + path.string());
}

static void testDepartments(const fs::path&) {
    QuanLyPhongBan manager;
    manager.themPhongBan(PhongBan("PB01", "Kinh doanh", "TP01", "Mo ta"));
    check(manager.timPhongBan("PB01") != nullptr, "khong tim thay phong ban vua them");
    check(manager.timPhongBan("PB01")->getTenPB() == "Kinh doanh", "sai ten phong ban");
    expectThrows<DuplicateException>(
        [&] { manager.themPhongBan(PhongBan("PB01", "Trung", "", "")); },
        "ma phong ban trung");
    expectThrows<InvalidInputException>(
        [&] { manager.themPhongBan(PhongBan("", "Khong ma", "", "")); },
        "ma phong ban rong");
    expectThrows<NotFoundException>(
        [&] { manager.xoaPhongBan("PB404"); },
        "xoa phong ban khong ton tai");
    check(manager.xoaPhongBan("PB01"), "xoa phong ban hop le that bai");
    check(manager.getDanhSach().empty(), "phong ban chua rong sau khi xoa");
}

static void testEmployeesAndPolymorphism(const fs::path&) {
    QuanLyNhanVien manager;
    manager.themNhanVien(makeFullTime());
    manager.themNhanVien(makePartTime());
    manager.themNhanVien(makeIntern());
    check(manager.getSoLuong() == 3, "khong tao du ba loai nhan vien");
    check(dynamic_cast<NhanVienFullTime*>(manager.timTheoMa("NVFT01")) != nullptr, "sai kieu Full-time");
    check(dynamic_cast<NhanVienPartTime*>(manager.timTheoMa("NVPT01")) != nullptr, "sai kieu Part-time");
    check(dynamic_cast<NhanVienThucTap*>(manager.timTheoMa("NVT01")) != nullptr, "sai kieu Intern");
    check(near(manager.timTheoMa("NVFT01")->getLuongGoc(), 10000000), "sai luong goc Full-time");
    check(near(manager.timTheoMa("NVPT01")->getLuongGoc(), 50000), "sai rate Part-time");
    check(near(manager.timTheoMa("NVT01")->getLuongGoc(), 25000), "sai rate Intern");
    check(manager.timTheoPhongBan("PB01").size() == 3, "sai tim theo phong ban");
    check(manager.timTheoTen("in").size() >= 1, "sai tim theo ten gan dung");
    expectThrows<DuplicateException>(
        [&] { manager.themNhanVien(makeFullTime("NVFT01")); }, "ma nhan vien trung");
    expectThrows<InvalidInputException>(
        [&] { manager.themNhanVien(makeFullTime("", 10000000)); }, "ma nhan vien rong");
    check(manager.xoaNhanVien("NVPT01"), "xoa nhan vien hop le that bai");
    expectThrows<NotFoundException>(
        [&] { manager.xoaNhanVien("NV404"); }, "xoa nhan vien khong ton tai");
}

static void testEmployeeRateValidation(const fs::path&) {
    const vector<double> invalidRates = {0.0, -1.0, numeric_limits<double>::quiet_NaN(),
                                               numeric_limits<double>::infinity()};
    for (double rate : invalidRates) {
        expectThrows<InvalidInputException>(
            [&] {
                QuanLyNhanVien manager;
                manager.themNhanVien(makePartTime("BAD", rate));
            },
            "rate Part-time khong hop le");
        expectThrows<InvalidInputException>(
            [&] {
                QuanLyNhanVien manager;
                manager.themNhanVien(makeIntern("BAD", rate));
            },
            "rate Intern khong hop le");
    }
    expectThrows<InvalidInputException>(
        [&] {
            QuanLyNhanVien manager;
            manager.themNhanVien(makeFullTime("BAD", 0));
        },
        "luong Full-time bang 0");
    expectThrows<InvalidInputException>(
        [&] {
            QuanLyNhanVien manager;
            manager.themNhanVien(makeFullTime("BAD", -1));
        },
        "luong Full-time am");
}

static void testAttendance(const fs::path&) {
    QuanLyChamCong manager;
    manager.themChamCong(ChamCong("CC01", "NVFT01", 1, 2024, 20, 2));
    check(manager.timChamCong("NVFT01", 1, 2024) != nullptr, "khong tim thay cham cong hop le");
    expectThrows<DuplicateException>(
        [&] { manager.themChamCong(ChamCong("CC02", "NVFT01", 1, 2024, 21, 0)); },
        "cham cong trung");
    expectThrows<InvalidInputException>(
        [&] { manager.themChamCong(ChamCong("CC02", "NVFT02", 0, 2024, 20, 0)); },
        "thang cham cong ngoai pham vi");
    expectThrows<InvalidInputException>(
        [&] { manager.themChamCong(ChamCong("CC03", "NVFT02", 1, 2024, 32, 0)); },
        "ngay cong vuot pham vi");
    expectThrows<InvalidInputException>(
        [&] { manager.themChamCong(ChamCong("CC04", "NVFT02", 1, 2024, -1, 0)); },
        "ngay cong am");
    expectThrows<InvalidInputException>(
        [&] { manager.themChamCong(ChamCong("CC05", "NVFT02", 1, 2024, 20, -1)); },
        "tang ca am");
    expectThrows<InvalidInputException>(
        [&] { manager.themChamCong(ChamCong("CC06", "NVFT02", 1, 2024, numeric_limits<double>::infinity(), 0)); },
        "ngay cong vo cuc");
}

static void testSalaryRules(const fs::path&) {
    vector<unique_ptr<NhanVien>> employees;
    employees.push_back(makeFullTime());
    employees.push_back(makePartTime());
    employees.push_back(makeIntern());

    ChamCong fullTimeAttendance("CCFT", "NVFT01", 1, 2024, 20, 2);
    ChamCong partTimeAttendance("CCPT", "NVPT01", 1, 2024, 10, 2);
    ChamCong internAttendance("CCIN", "NVT01", 1, 2024, 10, 2);

    check(near(employees[0]->tinhLuong(fullTimeAttendance), 10000000),
          "Full-time: ky vong 10000000");
    check(near(employees[1]->tinhLuong(partTimeAttendance), 4150000),
          "Part-time: ky vong 4150000");
    check(near(employees[2]->tinhLuong(internAttendance), 2000000),
          "Intern: ky vong 2000000");
    check(near(employees[0]->getTienTangCa(fullTimeAttendance), 300000),
          "Full-time: sai tien tang ca");
    check(near(employees[1]->getTienTangCa(partTimeAttendance), 150000),
          "Part-time: sai tien tang ca");
    check(near(employees[2]->getTienTangCa(internAttendance), 0),
          "Intern: tang ca phai bang 0");
}

static void testSalaryManager(const fs::path&) {
    QuanLyLuong manager;
    manager.themLuong(Luong("L01", "NVFT01", "Full-time", 1, 2024,
                            10000000, 9600000, 100000, 300000, 0, 10000000));
    check(manager.timLuong("NVFT01", 1, 2024) != nullptr, "khong tim thay bang luong");
    expectThrows<DuplicateException>(
        [&] {
            manager.themLuong(Luong("L02", "NVFT01", "Full-time", 1, 2024,
                                    10000000, 9600000, 100000, 300000, 0, 10000000));
        },
        "bang luong trung ky");
    expectThrows<InvalidInputException>(
        [&] { manager.themLuong(Luong("L03", "", "Full-time", 1, 2024, 1, 1, 0, 0, 0, 1)); },
        "ma nhan vien bang luong rong");
}

static void testPersistenceRoundTrip(const fs::path& root) {
    fs::create_directories(root);
    const fs::path departments = root / "phongban.txt";
    const fs::path employees = root / "nhanvien.txt";
    const fs::path attendance = root / "chamcong.txt";
    const fs::path salaries = root / "luong.txt";

    QuanLyPhongBan departmentManager;
    departmentManager.themPhongBan(PhongBan("PB01", "Kinh doanh", "TP01", "Mo ta"));
    departmentManager.saveToFile(departments.string());

    QuanLyNhanVien employeeManager;
    employeeManager.themNhanVien(makeFullTime());
    employeeManager.themNhanVien(makePartTime());
    employeeManager.themNhanVien(makeIntern());
    employeeManager.saveToFile(employees.string());

    QuanLyChamCong attendanceManager;
    attendanceManager.themChamCong(ChamCong("CCFT", "NVFT01", 1, 2024, 20, 2));
    attendanceManager.themChamCong(ChamCong("CCPT", "NVPT01", 1, 2024, 10, 2));
    attendanceManager.themChamCong(ChamCong("CCIN", "NVT01", 1, 2024, 10, 2));
    attendanceManager.saveToFile(attendance.string());

    QuanLyLuong salaryManager;
    salaryManager.themLuong(Luong("LFT", "NVFT01", "Full-time", 1, 2024,
                                  10000000, 9600000, 100000, 300000, 0, 10000000));
    salaryManager.themLuong(Luong("LPT", "NVPT01", "Part-time", 1, 2024,
                                  50000, 4000000, 0, 150000, 0, 4150000));
    salaryManager.themLuong(Luong("LIN", "NVT01", "Intern", 1, 2024,
                                  25000, 2000000, 25000, 0, 0, 2000000));
    salaryManager.saveToFile(salaries.string());

    QuanLyPhongBan loadedDepartments;
    QuanLyNhanVien loadedEmployees;
    QuanLyChamCong loadedAttendance;
    QuanLyLuong loadedSalaries;
    loadedDepartments.loadFromFile(departments.string());
    loadedEmployees.loadFromFile(employees.string());
    loadedAttendance.loadFromFile(attendance.string());
    loadedSalaries.loadFromFile(salaries.string());

    check(loadedDepartments.getDanhSach().size() == 1, "sai so phong ban sau khi doc");
    check(loadedEmployees.getSoLuong() == 3, "sai so nhan vien sau khi doc");
    check(dynamic_cast<NhanVienFullTime*>(loadedEmployees.timTheoMa("NVFT01")) != nullptr,
          "doc sai kieu Full-time");
    check(dynamic_cast<NhanVienPartTime*>(loadedEmployees.timTheoMa("NVPT01")) != nullptr,
          "doc sai kieu Part-time");
    check(dynamic_cast<NhanVienThucTap*>(loadedEmployees.timTheoMa("NVT01")) != nullptr,
          "doc sai kieu Intern");
    check(loadedAttendance.timChamCong("NVPT01", 1, 2024) != nullptr, "thieu cham cong sau khi doc");
    check(loadedSalaries.getDanhSach().size() == 3, "sai so bang luong sau khi doc");
    check(near(loadedSalaries.timLuong("NVPT01", 1, 2024)->getLuongThucNhan(), 4150000),
          "sai ket qua luong sau khi doc");
}

static void testSalaryFormats(const fs::path& root) {
    const fs::path oldNine = root / "salary-9.txt";
    const fs::path oldTen = root / "salary-10.txt";
    const fs::path current = root / "salary-11.txt";
    writeText(oldNine, "L9|NV9|1|2024|100|100|10|5|85\n");
    writeText(oldTen, "L10|NV10|1|2024|100|100|10|5|0|95\n");
    writeText(current, "L11|NV11|Full-time|1|2024|100|90|10|5|0|95\n");

    QuanLyLuong nine;
    QuanLyLuong ten;
    QuanLyLuong eleven;
    nine.loadFromFile(oldNine.string());
    ten.loadFromFile(oldTen.string());
    eleven.loadFromFile(current.string());
    check(nine.getDanhSach().size() == 1 && near(nine.getDanhSach()[0].getLuongThucNhan(), 85),
          "khong doc dung format luong 9 truong");
    check(ten.getDanhSach().size() == 1 && near(ten.getDanhSach()[0].getLuongThucNhan(), 95),
          "khong doc dung format luong 10 truong");
    check(eleven.getDanhSach().size() == 1 && eleven.getDanhSach()[0].getLoaiNV() == "Full-time",
          "khong doc dung format luong 11 truong");
}

static void testFileErrors(const fs::path& root) {
    const fs::path missing = root / "missing.txt";
    expectThrows<FileException>(
        [&] {
            QuanLyPhongBan manager;
            manager.loadFromFile(missing.string());
        },
        "file phong ban thieu");

    const fs::path malformedDepartment = root / "bad-department.txt";
    writeText(malformedDepartment, "PB01|Thieu truong\n");
    expectThrows<DataFormatException>(
        [&] {
            QuanLyPhongBan manager;
            manager.loadFromFile(malformedDepartment.string());
        },
        "dong phong ban sai format");

    const fs::path malformedAttendance = root / "bad-attendance.txt";
    writeText(malformedAttendance, "CC01|NV01|1\n");
    expectThrows<DataFormatException>(
        [&] {
            QuanLyChamCong manager;
            manager.loadFromFile(malformedAttendance.string());
        },
        "dong cham cong sai format");

    const fs::path malformedEmployee = root / "bad-employee.txt";
    writeText(malformedEmployee, "NV01|Ten|01|Nam|090|e|a|PB01|CV|01|Unknown|100|1\n");
    expectThrows<DataFormatException>(
        [&] {
            QuanLyNhanVien manager;
            manager.loadFromFile(malformedEmployee.string());
        },
        "loai nhan vien sai");

    const fs::path malformedSalary = root / "bad-salary.txt";
    writeText(malformedSalary, "L01|NV01|Unknown|1|2024|1|1|0|0|0|1\n");
    expectThrows<DataFormatException>(
        [&] {
            QuanLyLuong manager;
            manager.loadFromFile(malformedSalary.string());
        },
        "loai luong sai");
}

static void testEmptyFiles(const fs::path& root) {
    const fs::path empty = root / "empty.txt";
    writeText(empty, "");
    QuanLyPhongBan departments;
    QuanLyNhanVien employees;
    QuanLyChamCong attendance;
    QuanLyLuong salaries;
    departments.loadFromFile(empty.string());
    employees.loadFromFile(empty.string());
    attendance.loadFromFile(empty.string());
    salaries.loadFromFile(empty.string());
    check(departments.getDanhSach().empty(), "phong ban file rong khong cho danh sach rong");
    check(employees.getSoLuong() == 0, "nhan vien file rong khong cho danh sach rong");
    check(attendance.timTheoThang(1, 2024).empty(), "cham cong file rong khong cho danh sach rong");
    check(salaries.getDanhSach().empty(), "luong file rong khong cho danh sach rong");
}

static void testIntegratedFlow(const fs::path& root) {
    QuanLyPhongBan departments;
    departments.themPhongBan(PhongBan("PB01", "Kinh doanh", "TP01", "Mo ta"));

    QuanLyNhanVien employees;
    employees.themNhanVien(makeFullTime());
    employees.themNhanVien(makePartTime());
    employees.themNhanVien(makeIntern());

    QuanLyChamCong attendance;
    attendance.themChamCong(ChamCong("CCFT", "NVFT01", 1, 2024, 20, 2));
    attendance.themChamCong(ChamCong("CCPT", "NVPT01", 1, 2024, 10, 2));
    attendance.themChamCong(ChamCong("CCIN", "NVT01", 1, 2024, 10, 2));

    QuanLyLuong salaries;
    salaries.themLuong(Luong("LFT", "NVFT01", "Full-time", 1, 2024,
                             10000000, 9600000, 100000, 300000, 0, 10000000));
    salaries.themLuong(Luong("LPT", "NVPT01", "Part-time", 1, 2024,
                             50000, 4000000, 0, 150000, 0, 4150000));
    salaries.themLuong(Luong("LIN", "NVT01", "Intern", 1, 2024,
                             25000, 2000000, 25000, 0, 0, 2000000));

    fs::create_directories(root);
    departments.saveToFile((root / "phongban.txt").string());
    employees.saveToFile((root / "nhanvien.txt").string());
    attendance.saveToFile((root / "chamcong.txt").string());
    salaries.saveToFile((root / "luong.txt").string());

    QuanLyNhanVien reopenedEmployees;
    QuanLyLuong reopenedSalaries;
    reopenedEmployees.loadFromFile((root / "nhanvien.txt").string());
    reopenedSalaries.loadFromFile((root / "luong.txt").string());
    check(reopenedEmployees.getSoLuong() == 3, "luong tong hop mat nhan vien sau doc lai");
    check(near(reopenedSalaries.timLuong("NVFT01", 1, 2024)->getLuongThucNhan(), 10000000),
          "luong Full-time sai trong luong tong hop");
    check(near(reopenedSalaries.timLuong("NVPT01", 1, 2024)->getLuongThucNhan(), 4150000),
          "luong Part-time sai trong luong tong hop");
    check(near(reopenedSalaries.timLuong("NVT01", 1, 2024)->getLuongThucNhan(), 2000000),
          "luong Intern sai trong luong tong hop");
}

int main() {
    const fs::path root = fs::temp_directory_path() /
        ("qlns-acceptance-" + to_string(
            static_cast<unsigned long long>(
                chrono::high_resolution_clock::now().time_since_epoch().count())));
    fs::create_directories(root);

    const vector<pair<string, function<void(const fs::path&)>>> tests = {
        {"PB-02/PB-03/PB-04 Quan ly phong ban", testDepartments},
        {"NV-02/NV-03/NV-04/NV-05/NV-07/NV-08 Nhan vien", testEmployeesAndPolymorphism},
        {"NV-06 Kiem tra luong va rate", testEmployeeRateValidation},
        {"CC-02/CC-03/CC-04 Cham cong", testAttendance},
        {"LU-02/LU-03/LU-04/LU-05 Tinh luong da hinh", testSalaryRules},
        {"LU-06 Quan ly bang luong", testSalaryManager},
        {"TXT-01 Luu doc va khoi phuc doi tuong", testPersistenceRoundTrip},
        {"TXT-02 Format luong 9/10/11 truong", testSalaryFormats},
        {"TXT-03/TXT-04 Loi file va dong sai", testFileErrors},
        {"PB-01/CC-01/LU-06 File rong", testEmptyFiles},
        {"FLOW-01 Luong nghiep vu tong hop", testIntegratedFlow}
    };

    int passed = 0;
    int failed = 0;
    for (const auto& test : tests) {
        try {
            const fs::path caseRoot = root / ("case-" + to_string(passed + failed + 1));
            fs::create_directories(caseRoot);
            test.second(caseRoot);
            ++passed;
            cout << "PASS " << test.first << "\n";
        } catch (const exception& error) {
            ++failed;
            cout << "FAIL " << test.first << ": " << error.what() << "\n";
        } catch (...) {
            ++failed;
            cout << "FAIL " << test.first << ": loi khong xac dinh\n";
        }
    }

    cout << "\nSUMMARY: PASS=" << passed << " FAIL=" << failed
              << " TOTAL=" << tests.size() << "\n";
    error_code cleanupError;
    fs::remove_all(root, cleanupError);
    if (cleanupError) {
        cout << "WARNING: khong don duoc thu muc tam: " << root << "\n";
    }
    return failed == 0 ? 0 : 1;
}


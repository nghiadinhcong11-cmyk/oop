# TÀI LIỆU HỆ THỐNG QUẢN LÝ NHÂN SỰ (HRMS)

Hệ thống được phát triển bằng C++ theo mô hình hướng đối tượng (OOP), hỗ trợ quản lý toàn diện từ nhân sự, phòng ban đến chấm công và tính lương.

## 1. Danh sách các chức năng đã hoàn thành

### A. Quản lý Nhân viên (`QuanLyNhanVien`)
*   **Phân loại nhân sự**: Hỗ trợ 3 loại hình:
    *   **Full-time**: Nhân viên chính thức, lương tháng định mức.
    *   **Part-time**: Nhân viên bán thời gian, lương tính theo giờ.
    *   **Thực tập sinh**: Nhân viên thực tập, tính trợ cấp theo giờ.
*   **Thao tác**: Thêm mới, sửa thông tin, xóa nhân viên và xem danh sách toàn bộ.
*   **Ràng buộc**: Tự động kiểm tra trùng mã nhân viên khi thêm mới.

### B. Quản lý Phòng ban (`QuanLyPhongBan`)
*   Quản lý thông tin mã phòng, tên phòng, trưởng phòng và mô tả.
*   **Ràng buộc xóa**: Không cho phép xóa phòng ban nếu vẫn còn nhân viên thuộc phòng đó.
*   Hiển thị danh sách phòng ban dưới dạng bảng ngay ngắn.

### C. Quản lý Chấm công (`QuanLyChamCong`)
*   Ghi nhận số ngày công và số giờ tăng ca theo từng tháng/năm cho mỗi nhân viên.
*   Kiểm tra tính hợp lệ dữ liệu (tháng 1-12, số ngày công 0-31).
*   Mỗi nhân viên chỉ có một bản chấm công duy nhất trong một tháng của một năm.

### D. Module Tính lương & Phiếu lương (`QuanLyLuong`)
*   **Nguyên tắc bảo toàn**: Lương cơ bản gốc trong hồ sơ nhân viên được giữ nguyên, không bị ghi đè sau mỗi kỳ lương.
*   **Logic tính lương chi tiết**:
    *   **Full-time**: Định mức 24 ngày công. Dưới 24 ngày sẽ bị trừ 100.000đ cho mỗi ngày thiếu.
    *   **Part-time**: Lương = (Số ngày công * 8 * Lương giờ) + Tiền tăng ca.
    *   **Thực tập**: Trợ cấp = (Số ngày công * 8 * Mức trợ cấp/giờ).
*   **Các thành phần lương**: Tách biệt rõ ràng Lương gốc, Lương thực tế, Phụ cấp, Tăng ca, Khấu trừ.
*   **Khấu trừ**: Cho phép người quản lý nhập thêm các khoản trừ (bảo hiểm, thuế, phạt) khi tính lương.
*   **Phiếu lương**: In phiếu lương chi tiết cho từng nhân viên với đầy đủ các khoản điều chỉnh.
*   **Bảng lương tổng hợp**: Xem lại lịch sử lương của toàn bộ công ty hoặc theo tháng cụ thể.

### E. Tìm kiếm & Thống kê
*   Tìm kiếm nhân viên theo Mã, theo Tên (tìm kiếm gần đúng) hoặc theo Phòng ban.
*   Thống kê tổng số lượng nhân sự, số lượng theo từng loại (Full-time, Part-time,...) và cơ cấu nhân sự theo từng phòng ban.

## 2. Kỹ thuật và Định dạng
*   **Xử lý ngoại lệ (Exception Handling)**: Hệ thống sử dụng các class ngoại lệ tùy chỉnh (`DuplicateException`, `NotFoundException`, `InvalidInputException`) để ngăn chặn crash và thông báo lỗi rõ ràng cho người dùng.
*   **Lưu trữ dữ liệu**: Toàn bộ dữ liệu được lưu trữ dưới dạng file văn bản (`.txt`) với cơ chế Serialization/Deserialization tự động khi khởi động và đóng ứng dụng.
*   **Định dạng bảng biểu**: Sử dụng thư viện `iomanip` để căn lề trái/phải, tạo bảng ngay ngắn trên Console.
*   **Độ chính xác số thực**: Tất cả các con số liên quan đến tiền tệ và công xá được định dạng cố định với **2 chữ số thập phân**.
*   **Xử lý chuỗi**: Hàm tách chuỗi (split) được tối ưu hóa để xử lý chính xác các trường dữ liệu trống, tránh mất dữ liệu cũ khi cập nhật.

## 3. Cấu trúc lưu trữ dữ liệu
*   `data/nhanvien.txt`: Hồ sơ nhân sự gốc.
*   `data/phongban.txt`: Danh mục phòng ban.
*   `data/chamcong.txt`: Dữ liệu công xá hàng tháng.
*   `data/luong.txt`: Lịch sử bảng lương và phiếu lương đã tính.

---
*Tài liệu này liệt kê các nhiệm vụ cốt lõi đã được triển khai và cấu hình trong hệ thống oopcode.*

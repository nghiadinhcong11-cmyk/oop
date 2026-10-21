#!/usr/bin/env bash
set -u

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd -- "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="$SCRIPT_DIR/.build"
TEST_EXE="$BUILD_DIR/qlns-acceptance.exe"
LOG_FILE="$BUILD_DIR/build.log"
CXX="${CXX:-/c/msys64/ucrt64/bin/g++.exe}"

mkdir -p "$BUILD_DIR"

SOURCES=(
  "$SCRIPT_DIR/oop_acceptance.cpp"
  "$PROJECT_ROOT/models/ChamCong.cpp"
  "$PROJECT_ROOT/models/Luong.cpp"
  "$PROJECT_ROOT/models/NhanVien.cpp"
  "$PROJECT_ROOT/models/NhanVienFullTime.cpp"
  "$PROJECT_ROOT/models/NhanVienPartTime.cpp"
  "$PROJECT_ROOT/models/NhanVienThucTap.cpp"
  "$PROJECT_ROOT/models/PhongBan.cpp"
  "$PROJECT_ROOT/services/QuanLyChamCong.cpp"
  "$PROJECT_ROOT/services/QuanLyLuong.cpp"
  "$PROJECT_ROOT/services/QuanLyNhanVien.cpp"
  "$PROJECT_ROOT/services/QuanLyPhongBan.cpp"
)

echo "Building automatic tests with: $CXX"
if ! "$CXX" -std=c++17 -I"$PROJECT_ROOT" "${SOURCES[@]}" -o "$TEST_EXE" >"$LOG_FILE" 2>&1; then
  cat "$LOG_FILE"
  echo "TEST BUILD: BLOCKED"
  exit 2
fi

echo "Running automatic tests with isolated temporary data directories"
"$TEST_EXE"
TEST_EXIT=$?
echo "TEST_EXIT_CODE=$TEST_EXIT"
exit "$TEST_EXIT"


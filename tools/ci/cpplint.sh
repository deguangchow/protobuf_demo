echo "===================== cpplint begin ====================="

LOG_FILE="cpplint.log"

python tools/ci/cpplint.py --filter=\
-build/include,\
-build/c++11,\
-build/header_guard,\
-whitespace/comments,\
-whitespace/indent,\
-runtime/int,\
-runtime/references \
    --linelength=120 \
	$(find protobuf_demo/ -name "*.h") \
	$(find protobuf_demo/ -name "*.cpp") \
	$(find test/ -name "*.h") \
	$(find test/ -name "*.cpp") \
    > $LOG_FILE

echo "===================== cpplint end  ====================="


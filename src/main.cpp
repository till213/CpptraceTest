#include <exception>
#include <vector>

#include <QApplication>
#include <QString>
#include <QTextStream>
#include <QMessageBox>

#include <cpptrace/cpptrace.hpp>

#include "MainWindow.h"

namespace
{
    inline constexpr unsigned n_digits(unsigned value) {
        return value < 10 ? 1 : 1 + n_digits(value / 10);
    }

    QString formatTrace(const std::vector<cpptrace::stacktrace_frame> &trace) noexcept
    {
        QString stackTrace;
        QTextStream out(&stackTrace, QIODeviceBase::WriteOnly);

        std::size_t counter = 0;
        if (!trace.empty()) {
            out << "Stack trace (most recent call first):" << Qt::endl;
            const auto frame_number_width = n_digits(static_cast<int>(trace.size()) - 1);
            for(const auto &frame : trace) {
                out << '#'
                    << qSetFieldWidth(static_cast<int>(frame_number_width))
                    << Qt::left
                    << counter++
                    << Qt::right
                    << " "
                    << Qt::hex
                    << "0x"
                    << qSetFieldWidth(2 * sizeof(uintptr_t))
                    << qSetPadChar('0')
                    << frame.address
                    << qSetFieldWidth(0)
                    << Qt::dec
                    << qSetPadChar(' ')
                    << " in "
                    << QString::fromStdString(frame.symbol)
                    << " at "
                    << QString::fromStdString(frame.filename)
                    << ":"
                    << frame.line
                    << (frame.col > 0 ? ":" + QString::number(frame.col) : "")
                    << Qt::endl;
            }

        } else {
            out << "No stack trace available." << Qt::endl;
        }
        return stackTrace;
    }

    void handleTerminate()
    {
        cpptrace::print_trace();
        const auto trace = cpptrace::generate_trace();
        const QString traceString = ::formatTrace(trace);
        QMessageBox::critical(nullptr, "Termination", traceString);
        std::abort();
    }
}

int main(int argc, char *argv[])
{
    std::set_terminate(::handleTerminate);

    QApplication a(argc, argv);

    const auto trace = cpptrace::generate_trace();
    const QString traceString = ::formatTrace(trace);
    QMessageBox::critical(nullptr, "Termination", traceString);

    MainWindow w;

    w.show();
    return a.exec();
}

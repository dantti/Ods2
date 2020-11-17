#pragma once

#include "decl.hxx"
#include "global.hxx"
#include "ods.hxx"
#include "op.hh"
#include "style.hxx"

namespace ods { // ods::

template <class A_Type> class AutoDelete {
public:
	AutoDelete(A_Type x) : x_(x) {}
	virtual ~AutoDelete() { delete x_; }
	
private:
	A_Type x_ = nullptr;
};

template <class VecType> class AutoDeleteVec {
public:
	AutoDeleteVec(VecType &x) : vec_(x) {}
	~AutoDeleteVec() {
		for (auto *item : vec_) {
			delete item;
		}
	}
	
private:
	VecType &vec_;
};

ODS_API QString ToString(const Brace p);
ODS_API Brace FromString(const QString &s);

ODS_API void
ApplyBool(const QString &str, ods::Bool &b);

ODS_API CellRef*
CreateCellRef(Sheet *default_sheet, QStringRef address);

ODS_API double
DPI();

ODS_API void
DPI(const double dpi);

/** Returns the index of the last single quote, not past it. **/
int
FindEndOfSingleQuotedString(const QStringRef &s);

ODS_API int
FindNonAscii(const QStringRef &s, const int from = 0);

ODS_API int // error = -1
FindNonWhitespace(const QStringRef &str, const int from = 0);

ODS_API QString
FontSizeToString(const double size, const style::FontSizeType tp);

ODS_API int
ColumnLettersToNumber(const QStringRef &letters);

ODS_API QString
ColumnNumberToLetters(const int kColumn);

ODS_API ValueType
TypeFromString(const QString &ods_type);

ODS_API const char* // nullptr if not found
TypeToString(const ValueType value_type);

} // ods::

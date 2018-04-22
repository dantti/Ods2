#pragma once

#include "err.hpp"
#include "Prefix.hpp"

#include <QXmlStreamWriter>

namespace ods { // ods::

class Attr
{
public:
	Attr(ods::Prefix *prefix, const QString &name,
		const QString &value);
	virtual ~Attr();
	
	QString
	FullName() const;
	
	bool
	Is(ods::Prefix *prefix, const char *name) const;
	
	const QString&
	name() const { return name_; }
	
	ods::Prefix*
	prefix() const { return prefix_; }
	
	bool
	ToDouble(double &n);
	
	bool
	ToInt32(int32_t &n);
	
	const QString&
	value() const { return value_; }
	
	void
	Write(QXmlStreamWriter &xml);

private:
	NO_ASSIGN_COPY_MOVE(Attr);
	
	ods::Prefix *prefix_ = nullptr;
	QString name_;
	QString value_;
};

} // ods::
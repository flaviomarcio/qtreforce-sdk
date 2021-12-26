#ifndef Q_APR_VariantUtilTestUnit_H
#define Q_APR_VariantUtilTestUnit_H

#include "./qapr_test_unit.h"

namespace QApr{

    class Q_APR_VariantUtilTestUnit : public SDKGoogleTestUnit {
    public:
    };

    TEST_F(Q_APR_VariantUtilTestUnit, serviceStart)
    {
        EXPECT_TRUE(this->serviceStart())<<"fail: service start";
    }

    TEST_F(Q_APR_VariantUtilTestUnit, serviceStop)
    {
        EXPECT_TRUE(this->serviceStop())<<"fail: service stop";
    }

}

#endif

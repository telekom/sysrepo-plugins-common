#pragma once

#include <sysrepo-cpp/Session.hpp>

namespace srpc
{
/**
 * @brief Enum used for receiving comparison status between datastore values and values found on the system.
 */
enum class DatastoreValuesCheckStatus
{
    Equal,      ///< Values on the system are equal to those in the sysrepo datastore.
    Partial,    ///< Values on the system are partially equal to those in the sysrepo datastore. There are more values
                ///< contained on the system but all values from the datastore are contained on the system.
    NonExistant ///< Values from the datastore do not exist on the system.
};

/**
 * @brief Datastore values checking interface. Each class implementing this interface must check for datastore values on
 * the system and return the status code or throw an exception.
 */
class DatastoreValuesChecker
{
  public:
    /**
     * @brief Check for the datastore values on the system.
     *
     * @param session Sysrepo session used for retreiving datastore values.
     *
     * @return Enum describing the output of values comparison.
     */
    virtual DatastoreValuesCheckStatus checkValues(sysrepo::Session &session) = 0;
};
} // namespace srpc

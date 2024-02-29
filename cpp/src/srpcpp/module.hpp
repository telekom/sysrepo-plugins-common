#pragma once

#include "callbacks.hpp"
#include "datastore.hpp"
#include "context.hpp"

#include <list>

namespace srpc
{
/**
 * @brief Context interface. Used for passing context to each callback.
 */
class IModuleContext
{
};

/**
 * @brief Module interface.
 * @brief Each module should define its own callbacks and its own modules to use as parameters to callback classes.
 */
template <PluginContext PluginContextType> class IModule
{
  public:
    /**
     * Default constructor.
     */
    IModule(PluginContextType &plugin_ctx) : m_pluginContext(plugin_ctx)
    {
    }

    /**
     * Return the plugin context reference.
     */
    PluginContextType &getPluginContext()
    {
        return m_pluginContext;
    }

    /**
     * Get all operational callbacks which the module should use.
     */
    virtual std::list<OperationalCallback> getOperationalCallbacks() = 0;

    /**
     * Get all module change callbacks which the module should use.
     */
    virtual std::list<ModuleChangeCallback> getModuleChangeCallbacks() = 0;

    /**
     * Get all RPC callbacks which the module should use.
     */
    virtual std::list<RpcCallback> getRpcCallbacks() = 0;

    /**
     * Get all datastore initializers that this module provides.
     */
    std::list<std::shared_ptr<IDatastoreInitializer>> getDatastoreInitializers()
    {
        return m_datastore_initializers;
    }

    /**
     * Get all datastore value checkers that this module provides.
     */
    std::list<std::shared_ptr<IDatastoreChecker>> getValueCheckers()
    {
        return m_checkers;
    }

    /**
     * Get all datastore value appliers that this module provides.
     */
    std::list<std::shared_ptr<IDatastoreApplier>> getValueAppliers()
    {
        return m_appliers;
    }

    /**
     * Get module name.
     */
    virtual constexpr const char *getName() = 0;

    /**
     * Virtual destructor.
     */
    virtual ~IModule()
    {
    }

  protected:
    /**
     * @brief Add a datastore initializer to the module.
     */
    template <DatastoreValueInitializer InitializerType> void addDatastoreInitializer(std::shared_ptr<InitializerType>& initializer)
    {
        m_datastore_initializers.push_back(initializer);
    }

    /**
     * @brief Add a value checker to the module.
     */
    template <DatastoreValueChecker CheckerType> void addValueChecker(std::shared_ptr<CheckerType>& checker)
    {
        m_checkers.push_back(checker);
    }

    /**
     * @brief Add a value applier to the module.
     */
    template <DatastoreValueApplier ApplierType> void addValueApplier(std::shared_ptr<ApplierType>& applier)
    {
        m_appliers.push_back(applier);
    }

  private:
    std::list<std::shared_ptr<IDatastoreInitializer>> m_datastore_initializers; ///< Plugin datastore initializers.
    std::list<std::shared_ptr<IDatastoreChecker>> m_checkers; ///< Plugin data checkers.
    std::list<std::shared_ptr<IDatastoreApplier>> m_appliers; ///< Plugin datastore data appliers.
    PluginContextType &m_pluginContext; ///< Plugin context used to share data between different parts of the module.
};

/**
 * @brief Module concept used for determining valid module type at compile time.
 */
template <typename T, typename PluginContextType>
concept PluginModule = std::is_base_of<IModule<PluginContextType>, T>::value;
} // namespace srpc

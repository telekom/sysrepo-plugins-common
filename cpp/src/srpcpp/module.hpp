#pragma once

#include "callbacks.hpp"
#include "ds-check.hpp"

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
template <typename PluginContextType> class IModule
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
     * Return the operational context from the module.
     */
    virtual std::shared_ptr<IModuleContext> getOperationalContext() = 0;

    /**
     * Return the module changes context from the module.
     */
    virtual std::shared_ptr<IModuleContext> getModuleChangesContext() = 0;

    /**
     * Return the RPC context from the module.
     */
    virtual std::shared_ptr<IModuleContext> getRpcContext() = 0;

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
     * Get all system value checkers that this module provides.
     */
    std::list<std::shared_ptr<DatastoreValuesChecker<PluginContextType>>> getValueCheckers()
    {
        return m_checkers;
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
     * @brief Add a value checker to the module.
     *
     * @param checker Pointer to the value checker to add.
     */
    template <typename CheckerType> void addValueChecker()
    {
        m_checkers.push_back(std::make_shared<CheckerType>(m_pluginContext));
    }

  private:
    std::list<std::shared_ptr<DatastoreValuesChecker<PluginContextType>>> m_checkers; ///< Plugin data checkers.
    PluginContextType &m_pluginContext; ///< Plugin context used to share data between different parts of the module.
};
} // namespace srpc

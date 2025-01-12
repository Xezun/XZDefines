#
# Be sure to run `pod lib lint XZDefines.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#



Pod::Spec.new do |s|
  s.name             = 'XZDefines'
  s.version          = '2.0.0'
  s.summary          = 'XZKit 的基础部分'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
                       XZDefines 包含 XZKit 中常用的一些基础定义。
                       DESC

  s.homepage         = 'https://github.com/Xezun/XZDefines'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'Xezun' => 'developer@xezun.com' }
  s.source           = { :git => 'https://github.com/Xezun/XZDefines.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '12.0'
  s.pod_target_xcconfig = { 'GCC_PREPROCESSOR_DEFINITIONS' => 'XZ_FRAMEWORK=1' }
  
  s.default_subspec = 'Code'
  
  s.subspec 'Code' do |ss|
    ss.public_header_files = 'XZDefines/Code/**/*.h'
    ss.source_files        = 'XZDefines/Code/**/*.{h,m}'
  end
  
  s.subspec 'DEBUG' do |ss|
    ss.dependency 'XZDefines/Code'
    ss.pod_target_xcconfig = { 'GCC_PREPROCESSOR_DEFINITIONS' => 'XZ_DEBUG=1' }
  end
  
  # s.resource_bundles = {
  #   'XZDefines' => ['XZDefines/Assets/*.png']
  # }

  # s.public_header_files = 'Pod/Classes/**/*.h'
  # s.frameworks = 'UIKit', 'MapKit'
  # s.dependency 'AFNetworking', '~> 2.3'
  
  
  def s.defineSubspec(name, dependencies)
    self.subspec name do |ss|
      ss.public_header_files = "XZDefines/Code/#{name}/**/*.h";
      ss.source_files        = "XZDefines/Code/#{name}/**/*.{h,m}";
      for dependency in dependencies
        ss.dependency dependency;
      end
    end
  end
  
  s.defineSubspec 'XZEmpty',      ['XZDefines/XZMacro'];
  s.defineSubspec 'XZDefer',      ['XZDefines/XZMacro'];
  s.defineSubspec 'XZMacro',      [];
  s.defineSubspec 'XZRuntime',    [];
  s.defineSubspec 'XZUtils',      [];

end

